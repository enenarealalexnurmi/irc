#include "User.hpp"

User::User(int sockfd, const std::string &hostname, std::string &servername) :
sockfd(sockfd), hostname(hostname), servername(servername), flags(RECEIVENOTICE)
{}

int		User::getSockfd() const
{
	return sockfd;
}

const std::string	User::getUsername() const
{
	return username;
}

const std::string	User::getHostname() const
{
	return hostname;
}

const std::string	User::getServername() const
{
	return servername;
}

const std::string	User::getNickname() const
{
	return nickname;
}

const std::string	User::getRealname() const
{
	return realname;
}

const std::string	User::getPassword() const
{
	return password;
}

const std::string	User::getExitMessage() const
{
	return exitMessage;
}

const std::string	User::getAwayMessage() const
{
	return awayMessage;
}

std::string	User::getPrefix() const
{
	return std::string(nickname + "!" + username + "@" + hostname);
}

time_t	User::getTimeRegistration() const
{
	return timeRegistration;
}

time_t	User::getTimeLastMessage() const
{
	return timeLastMessage;
}

time_t	User::getTimePing() const
{
	return timePing;
}

const std::queue<std::string>	User::getMessages() const
{
	return messages;
}

int		User::readMessage()
{
	char buffer[512];
	int bytesRead;
	std::string	text;
	int slen = 512;

    bytesRead = recv(sockfd, buffer, slen, 0);
	while ((bytesRead > 0) && (buffer[bytesRead - 1] != '\n'))
	{
		buffer[bytesRead] = 0;
		text += buffer;
		buffer[0] = 0;
		slen -= bytesRead;
		bytesRead = recv(sockfd, buffer, slen, 0);
	}
	text += buffer;
	if (messages.size() > 0)
		text = messages.front();
	if (text.length() == 512)
		text = text.substr(0, 510) + "\r\n";
	if (bytesRead <= 0)
		return -1;
	while (text.find("\r\n") != std::string::npos)
		text.replace(text.find("\r\n"), 2, "\n");
	std::cout << "msg text: " << text << std::endl; //delete
	return (512 - slen);
}

void	User::sendMessage(const std::string &msg) const
{
	if (msg.size() > 0)
		send(sockfd, msg.c_str(), msg.size(), 0);
}

void	User::popMessage()
{
	if (messages.size() > 0)
		messages.pop();
}

void	User::setPassword(const std::string &str)
{
	password = str;
}

void	User::setUsername(const std::string &str)
{
	username = str;
}

void	User::setHostname(const std::string &str)
{
	hostname = str;
}

void	User::setNickname(const std::string &str)
{
	nickname = str;
}

void	User::setRealname(const std::string &str)
{
	realname = str;
}

void	User::setAwayMessage(const std::string &msg)
{
	awayMessage = msg;
}

void	User::updateTimeLastMessage()
{
	timeLastMessage = time(0);
}

void	User::updateTimePing()
{
	timePing = time(0);
}

void	User::setExitMessage(const std::string &str)
{
	exitMessage = str;
}

unsigned char	User::getFlags() const
{
	return flags;
}

void	User::setFlag(unsigned char flag)
{
	flags |= flag;
	if (flag == BREAKCONNECTION && exitMessage.size() == 0)
		exitMessage = "Client exited";
}

/*const std::vector<const Channel *>	&User::getChannels() const
{
	return channels;
};

bool	User::isOnChannel(const std::string &name) const
{
	for (size_t i = 0; i < channels.size(); i++)
		if (channels[i]->getName() == name)
			return true;
	return false;
}

void	User::removeChannel(const std::string &name)
{
	std::vector<const Channel *>::iterator	begin = channels.begin();
	std::vector<const Channel *>::iterator	end = channels.end();
	for (; begin != end; ++begin)
		if ((*begin)->getName() == name)
			break ;
	channels.erase(begin);
}

void	User::addChannel(const Channel &channel)
{
	channels.push_back(&channel);
}*/