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

// const std::queue<std::string>	User::getMessages() const
// {
// 	return messages;
// }

Message*	User::getMessage() const
{
	return new Message(this->getSockfd());
}

void	User::sendMessage(const Message& msg) const
{
	msg.sendIt(this->getSockfd());
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

std::vector<Channel *>	User::getChannels()
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
	std::vector<Channel *>::iterator	begin = channels.begin();
	std::vector<Channel *>::iterator	end = channels.end();
	for (; begin != end; ++begin)
		if ((*begin)->getName() == name)
			break ;
	channels.erase(begin);
}

void	User::addChannel(Channel &channel)
{
	channels.push_back(&channel);
}
