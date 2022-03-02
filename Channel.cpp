#include "Channel.hpp"

Channel::Channel(const std::string &name, User &creator, const std::string &pass) :
		_name(name), _pass(pass), _limit(0), _flags(NOMESSAGE)
{
	_users.push_back(&creator);
	_operators.push_back(&creator);
	//sendInfo(creator);
}

Channel::~Channel()
{}

const std::string	Channel::getName() const
{
	return (_name);
}

const std::string	Channel::getTopic() const
{
	return (_topic);
}

unsigned char	Channel::getFlags() const
{
	return (_flags);
}

void	Channel::setTopic(User &user, const std::string &topic)
{
	std::string msg;

	if ((_flags & TOPICSET) && !isOperator(user))
		sendError(user, ERR_CHANOPRIVSNEEDED, _name, "");
	else
	{
		this->_topic = topic;
		msg = "TOPIC " + _name + " :" + this->_topic + "\n";
		sendMessage(msg, user, true);
	}
}

void	Channel::setPass(User &user, const std::string &pass)
{
	if (_pass.size() > 0 && pass.size() > 0)
		sendError(user, ERR_KEYSET, _name, "");
	else
		this->_pass = pass;
}

void	Channel::sendInfo(User &user)
{
	std::string	names;
	std::vector<const User *>::const_iterator	begin = _users.begin();
	std::vector<const User *>::const_iterator	end = _users.end();
	std::string msg = "JOIN :" + _name + "\n";

	sendMessage(msg, user, true);
	if (_topic.size() > 0)
		sendReply(user, RPL_TOPIC, _name, _topic, "", "");
	else
		sendReply(user, RPL_NOTOPIC, _name, "", "", "");
	while (begin != end)
	{
		const User	*tmp = *begin;
		if (isOperator(*tmp))
			names += "@";
		else if (isSpeaker(*tmp))
			names += "+";
		names += tmp->getNickname();
		++begin;
		if (begin != end)
			names += " ";
	}
	sendReply(user, RPL_NAMREPLY, "= " + _name, names, "", "");
	sendReply(user, RPL_ENDOFNAMES, _name, "", "", "");
}

bool	Channel::isOperator(const User &user) const
{
	for (size_t i = 0; i < _operators.size(); i++)
		if (_operators[i]->getPrefix() == user.getPrefix())
			return true;
	return false;
}

bool	Channel::isSpeaker(const User &user) const
{
	for (size_t i = 0; i < _speakers.size(); i++)
		if (_speakers[i]->getPrefix() == user.getPrefix())
			return true;
	return false;
}

void	Channel::sendMessage(std::string &message, User &from, bool includeUser) const
{
	std::string	msg;
	msg += ":" + from.getPrefix() + " " + message;
	std::vector<User *>::const_iterator	begin = _users.begin();
	std::vector<User *>::const_iterator	end = _users.end();
	for (; begin != end; ++begin)
	{
		if (includeUser || *begin != &from)
			(*begin)->sendMessage(msg);
	}
}

bool	Channel::isInChannel(const std::string &nickname) const
{
	
	for (std::vector<User *>::const_iterator it = _users.begin(); it != _users.end(); ++it)
		if ((*it)->getNickname() == nickname)
		return (true);
	return (false);
}

bool	Channel::isEmpty() const
{
	if (_users.size() == 0)
		return true;
	return false;
}
