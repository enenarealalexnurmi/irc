#include "Server.hpp"
#include "PassCmd.hpp"

Server::Server (int port, const std::string password) :
	port(port), 
	password(password),
	servername(config.get("servername")),
	version(config.get("version")),
	debuglvl(config.get("debuglvl")),
	comments(config.get("comments")),
	timeout(atoi(config.get("timeout").c_str())),
	maxChannels(atoi(config.get("maxChannels").c_str()))
{
	callCmd = new CommandFactory(this);
	socketFd = createSocket();
	bzero(&sockaddr, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockaddr.sin_port = htons(port);
	loadfile(&motd, "./configs/motd.txt");
	loadfile(&info, "./configs/info.txt");
}

Server::Server(const Server& other)
{
	this->port = other.port;
	this->socketFd = other.socketFd;
	this->password = other.password;
	this->sockaddr = other.sockaddr;
	this->userPollFds = other.userPollFds;
	this->config = other.config;
	this->motd = other.motd;
	this->info = other.info;
	this->servername = other.servername;
	this->connectedUsers = other.connectedUsers;
	this->callCmd = other.callCmd;
	this->timeout = other.timeout;
	this->channels = other.channels;
}

int	 Server::createSocket()
{
	int fd;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
	{
		std::cout << RED << "SERVER ERROR: " << STOP << "establishing soket error.\n";
		exit(1);
	}
	std::cout << GREEN << "Socket was created successfully.\n" << STOP;
	return (fd);
}

void Server::serverMagic()
{
	int enable;

	enable = 1;
	if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
	{
		std::cout << RED << "SERVER ERROR: " << STOP << "setsockopt failed.\n";
		exit(1);
	}
	std::cout << GREEN << "Options for socket was settled successfully.\n" << STOP;
	if (bind(socketFd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0)
	{
		std::cout << RED << "SERVER ERROR: " << STOP << "unable to bind to port.\n";
		exit(1);
	}
	std::cout << GREEN << "Socket was binded successfully.\n" << STOP;
	if (listen(socketFd, 128) < 0)
	{
		std::cout << RED << "SERVER ERROR: " << STOP << "unable to bind to port.\n";
		exit(1); 
	}
	std::cout << GREEN << "Listening started successfully.\n" << STOP;
	if (fcntl(socketFd, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cout << RED << "SERVER ERROR: " << STOP << "file controle (fcntl) failed.\n";
		exit(1);
	}
	std::cout << GREEN << "Non-blocking mode for files was settled successfully.\n" << STOP;
}

void Server::executeLoop()
{
	unsigned int		addressSize;
	int				 connectFd;
	char				host[16];
		
	addressSize = sizeof(sockaddr);
	connectFd = accept(socketFd, (struct sockaddr *)&sockaddr, &addressSize);
	if (connectFd >= 0)
	{
		inet_ntop(AF_INET, &(sockaddr.sin_addr), host, 16);
		userPollFds.push_back(pollfd());
		userPollFds.back().fd = connectFd;
		userPollFds.back().events = POLLIN;
		userPollFds.back().revents = 0;
		connectedUsers.push_back(new User(connectFd, host, servername));
	}
	receiveMessage();
	pingMonitor();
	deleteUsers();
	deleteChannels();
}

void Server::receiveMessage()
{
	int pret;
	int ping;
	size_t i;

	ping = atoi(config.get("ping").c_str());
	pret = poll(&userPollFds[0], userPollFds.size(), (ping * 1000)/10);
	if (pret == -1)
		return ;
	if (pret != 0)
	{
		for (i = 0; i < userPollFds.size(); i++)
		{
			if (userPollFds[i].revents == POLLIN)
			{
				std::cout << "1" << std::endl;
				Message* msg = connectedUsers[i]->getMessage();
				while (msg)
				{
					std::cout << "2" << std::endl;
					ACommand* cmd = NULL;
					try
					{
						cmd = callCmd->createCommand(*msg, connectedUsers[i]);
						manageCommand(cmd);
					}
					catch(const Error& e)
					{
						Message* forSend = e.getMessage();
						forSend->sendIt(connectedUsers[i]->getSockfd());
						delete forSend;
					}
					std::cout << "3" << std::endl;
					connectedUsers[i]->updateTimeLastMessage();
					if (!cmd)
						delete cmd;
					delete msg;
					msg = connectedUsers[i]->getMessage();
				}
				std::cout << "4" << std::endl;
			}
			userPollFds[i].revents = 0;
		}
	}
}

void Server::manageCommand(ACommand* cmd)
{
	try
	{
		if (cmd->isAllowed())
		{
			cmd->execute();
		}
		else
			cmd->whyNotAllowed();
	}
	catch(const Error& e)
	{
		Message* forSend = e.getMessage();
		forSend->sendIt(cmd->getSender()->getSockfd());
		delete forSend;
	}
}

void Server::pingMonitor()
{
	for (size_t i = 0; i < connectedUsers.size(); i++)
	{
		if (connectedUsers[i]->getFlags() & REGISTERED)
		{
			if (time(0) - connectedUsers[i]->getTimeLastMessage() > static_cast<time_t>(timeout))
			{
				connectedUsers[i]->sendMessage(Message(":" + this->servername + " PING :" + this->servername + "\n"));
				connectedUsers[i]->updateTimePing();
				connectedUsers[i]->updateTimeLastMessage();
				connectedUsers[i]->setFlag(PINGING);
			}
			if ((connectedUsers[i]->getFlags() & PINGING) && (time(0) - connectedUsers[i]->getTimePing() > static_cast<time_t>(timeout)))
				connectedUsers[i]->setFlag(BREAKCONNECTION);
		}
	}
}

void Server::deleteUsers()
{
	size_t count;
	std::string nick;
	std::vector<Channel *> lastBreath;

	count = connectedUsers.size();
	for (size_t i = 0; i < count; ++i)
	{
		if (connectedUsers[i]->getFlags() & BREAKCONNECTION)
		{
			nick = connectedUsers[i]->getNickname();
			notifyUsersAbout(*(connectedUsers[i]),
				Message(connectedUsers[i]->getUsername() + " " + connectedUsers[i]->getHostname() + " * " + connectedUsers[i]->getRealname()));
			close(connectedUsers[i]->getSockfd());
			delete connectedUsers[i];
			connectedUsers.erase(connectedUsers.begin() + i);
			userPollFds.erase(userPollFds.begin() + i);
			--i;
		}
	}
}

void Server::deleteChannels()
{
	std::map<std::string, Channel *>::const_iterator it = channels.begin();
	size_t count = channels.size();
	for (size_t i = 0; i < count; ++i)
	{
		if ((*it).second->isEmpty())
		{
			delete (*it).second;
			channels.erase((*it).first);
			it = channels.begin();
		}
		else
			++it;
	}
}

bool Server::isPrivilegedOperator(std::string nickname, std::string password)
{
	return (nickname == config.get("operatorName") && password == config.get("operatorPassword"));
}

std::string Server::getPassword()
{
	return password;
}

std::vector<std::string> Server::getMotd()
{
	return motd;
}

std::vector<std::string> Server::getInfo()
{
	return info;
}

std::string Server::getServername()
{
	return servername;
}

std::vector<User *> Server::getConnectedUsers()
{
	return connectedUsers;
}

id_t Server::getTimeout()
{
	return timeout;
}

size_t Server::getMaxChannels()
{
	return maxChannels;
}

std::map<std::string, Channel *> Server::getChannels()
{
	return channels;
}

bool	Server::hasNickname(const std::string &nickname) const
{
	bool	ret = false;
	size_t	usersCount = this->connectedUsers.size();
	size_t	i = 0;

	while (!ret && i < usersCount)
	{
		if (connectedUsers[i]->getNickname() == nickname)
			ret = true;
		i++;
	}
	return (ret);
}

std::string Server::getVersion()
{
	return version;
}

std::string Server::getDebuglvl()
{
	return debuglvl;
}

std::string Server::getComments()
{
	return comments;
}

void	Server::rereadConfig()
{
	config.reread();
}

int		Server::getSockfd()
{
	return socketFd;
}

bool	Server::hasChannel(const std::string &channelname) const
{
	try
	{
		channels.at(channelname);
		return true;
	}
	catch(const std::exception& e)
	{}
	return false;
}

void	Server::notifyUsersAbout(User &user, const Message &notification)
{
	const std::vector<Channel *> chans = user.getChannels();
	for (size_t i = 0; i < connectedUsers.size(); i++)
	{
		for (size_t j = 0; j < chans.size(); j++)
		{
			if (chans[j]->isInChannel(connectedUsers[i]->getNickname()))
			{
				notification.sendIt(connectedUsers[i]->getSockfd());
				break;
			}
		}
	}
}

void	Server::checkRegistration(User &user)
{
	std::cout << "check reg" << std::endl;
	if (user.getNickname().size() > 0 && user.getUsername().size() > 0)
	{
		std::cout << "has nick and real name" << std::endl;
		if (password.size() == 0 || user.getPassword() == password)
		{
			std::cout << "pass correct" << std::endl;
			if (!(user.getFlags() & REGISTERED))
			{
				user.setFlag(REGISTERED);
				std::vector<std::string>::iterator ite = this->getMotd().end();
				std::vector<std::string>::iterator it = this->getMotd().begin(); (void)ite;
				// for (std::vector<std::string>::iterator it = this->getMotd().begin(); it < ite; it++)
				// {
					std::string out = *it;
					std::cout << out;
					//Message(out).sendIt(user.getSockfd());
				// }
					it++;
					out = *it;
					std::cout << out;
			}
		}
		else
			user.setFlag(BREAKCONNECTION);
	}
}

User	*Server::getUserByName(const std::string &name)
{
	User	*ret;
	size_t	usersCount = connectedUsers.size();
	for (size_t i = 0; i < usersCount; i++)
		if (connectedUsers[i]->getNickname() == name)
			ret = connectedUsers[i];
	return ret;
}

Server::~Server()
{  
	for (size_t i = 0; i < connectedUsers.size(); ++i)
	{
		close(connectedUsers[i]->getSockfd());
		delete connectedUsers[i];
	}
	std::map<std::string, Channel *>::const_iterator	beg = channels.begin();
	std::map<std::string, Channel *>::const_iterator	end = channels.end();
	for (; beg != end; ++beg)
		delete (*beg).second;
	close(socketFd);
	delete callCmd;
}