#include "Channel.hpp"

Channel::Channel(const std::string &name, User &creator, const std::string &pass) :
		_name(name), _pass(pass), _limit(0), _flags(NOMESSAGE)
{
	_users.push_back(&creator);
	_operators.push_back(&creator);
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

void	Channel::setLimit(unsigned short limit)
{
	_limit = limit;
}

void	Channel::setTopic(User &user, const std::string &topic)
{
	std::string msg;

	if ((_flags & TOPICSET) && !isOperator(user))
		throw Error(Error::ERR_CHANOPRIVSNEEDED, &user, _name);
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
		throw Error(Error::ERR_KEYSET, &user, _name);
	else
		this->_pass = pass;
}

void	Channel::printCreateInfo(User &user)
{
	std::string	names;
	std::vector<User *>::const_iterator	begin = _users.begin();
	std::vector<User *>::const_iterator	end = _users.end();
	std::string msg = "JOIN :" + _name + "\n";

	sendMessage(msg, user, true);
	if (_topic.size() > 0)
		sendReply(user, RPL_TOPIC, _name, _topic, "", "");
	else
		sendReply(user, RPL_NOTOPIC, _name, "", "", "");
	while (begin != end)
	{
		User	*tmp = *begin;
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
}

bool	Channel::isOperator(User &user) const
{
	for (size_t i = 0; i < _operators.size(); i++)
		if (_operators[i]->getPrefix() == user.getPrefix())
			return true;
	return false;
}

bool	Channel::isSpeaker(User &user) const
{
	for (size_t i = 0; i < _speakers.size(); i++)
		if (_speakers[i]->getPrefix() == user.getPrefix())
			return true;
	return false;
}

void	Channel::sendMessage(const std::string &message, User &from, bool includeUser) const
{
	std::vector<User *>::const_iterator	begin = _users.begin();
	std::vector<User *>::const_iterator	end = _users.end();
	Message	msg(":" + from.getPrefix() + " " + message);

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
	return(_users.size() == 0);
}

bool	Channel::isInvite(User &user) const
{
	for (size_t i = 0; i < _invited_users.size(); i++)
		if (_invited_users[i]->getPrefix() == user.getPrefix())
			return true;
	return false;
}

bool	Channel::isBanned(const std::string &mask, const std::string &prefix)
{
	const char 	*s = prefix.c_str();
	const char 	*p = mask.c_str();
	const char 	*rs=0;
	const char	*rp;

	while (true)
	{
		if (*p == '*')
		{
			rs = s;
			rp = ++p;
		}
		else if (!*s)
		{
			return (!(*p));
		}
		else if (*s == *p)
		{
			++s;
			++p;
		}
		else if (rs)
		{
			s = ++rs;
			p = rp;
		}
		else
		{
			return (false);
		}
	}
}

std::string	Channel::printFlag() const
{
	std::string	ret;

	if (_flags & INVITEONLY)
		ret += "i";
	if (_flags & NOMESSAGE)
		ret += "n";
	if (_flags & PRIVATE)
		ret += "p";
	if (_flags & SECRET)
		ret += "s";
	if (_flags & TOPICSET)
		ret += "t";
	return ret;
}

void	Channel::printChannelInfo(User &user)
{
	std::string			name;
	std::string			info;
	std::stringstream	s;

	if ((_flags & SECRET) && !isInChannel(user.getNickname()))
		return ;
	if ((_flags & PRIVATE) && !isInChannel(user.getNickname()))
		name = "*";
	else
	{
		name = _name;
		info = "[+" + printFlag() + "] " + _topic;
	}

	s << _users.size();
	sendReply(user, RPL_LIST, name, s.str(), info, "");
}

void	Channel::addBanMasks(const std::string &mask)
{
	_ban_masks.push_back(mask);
}

void	Channel::delBanMasks(const std::string &mask)
{
	size_t i;
	for ( i = 0; i < _ban_masks.size(); i++)
		if (_ban_masks[i] == mask)
			break;
	_ban_masks.erase(_ban_masks.begin() + i);
}

void	Channel::addSpeaker(User &user)
{
	if (!isSpeaker(user))
		_speakers.push_back(&user);
}

void	Channel::delSpeaker(User &user)
{
	size_t i;

	if (isSpeaker(user))
	{
		for (i = 0; i < _speakers.size(); i++)
			if (_speakers[i] == &user)
				break;
		_speakers.erase(_speakers.begin() + i);
	}
}

void	Channel::addOperator(User &user)
{
	if (!isOperator(user))
		_operators.push_back(&user);
}

void	Channel::delOperator(User &user)
{
	size_t i;
	if (isOperator(user))
	{
		for (i = 0; i < _operators.size(); i++)
			if (_operators[i] == &user)
				break;
		_operators.erase(_operators.begin() + i);
		if (_operators.size() == 0 && _users.size() > 0)
		{
			_operators.push_back(_users[0]);
			sendMessage("MODE " + this->_name + " +o "  + _users[0]->getNickname() + "\n", user, true);
		}
	}
}

void	Channel::addInvite(User &user, User &receiver)
{
	if (_flags & INVITEONLY && !isOperator(user))
		throw Error(Error::ERR_CHANOPRIVSNEEDED, &user, _name);
	else
	{
		_invited_users.push_back(&receiver);
		receiver.sendMessage(":" + user.getPrefix() + " INVITE " + receiver.getNickname() + " :" + _name + "\n");
		sendReply(user, RPL_INVITING, _name, receiver.getNickname(), "", "");
		if (receiver.getFlags() & AWAY)
			sendReply( user, RPL_AWAY, receiver.getNickname(), receiver.getAwayMessage(), "", "");
	}
}

void	Channel::delInvite(User &user)
{
	size_t i;
	if (isInvite(user))
	{
		for (i = 0; i < _invited_users.size(); i++)
			if ((*_invited_users[i]).getNickname() == user.getNickname())
				break;
		_invited_users.erase(_invited_users.begin() + i);
	}
}

void	Channel::addFlag(unsigned char flag)
{
	_flags |= flag;
}

void	Channel::delFlag(unsigned char flag)
{
	_flags &= ~flag;
}

void	Channel::addConnect(User &user, const std::string &key)
{
	std::vector<User *>::iterator	begin = _users.begin();
	std::vector<User *>::iterator	end = _users.end();

	if ((_flags & PRIVATE) && key != _pass)
		throw Error(Error::ERR_BADCHANNELKEY, &user, _name);
	else if (_limit != 0 && _users.size() >= _limit)
		throw Error(Error::ERR_CHANNELISFULL, &user, _name);
	else if ((_flags & INVITEONLY) && !isInvite(user))
		throw Error(Error::ERR_INVITEONLYCHAN, &user, _name);
	else
	{
		for (size_t i = 0; i < _ban_masks.size(); i++)
		{
			if (isBanned(_ban_masks[i], user.getPrefix()))
			{
				throw Error(Error::ERR_BANNEDFROMCHAN, &user, _name);
				return ;
			}
		}
		for (; begin != end; ++begin)
			if ((*begin)->getPrefix() == user.getPrefix())
				return ;
		_users.push_back(&user);
		delInvite(user);
		printCreateInfo(user);
	}
}

void	Channel::delConnect(User &user)
{
	std::vector<User *>::iterator	begin = _users.begin();
	std::vector<User *>::iterator	end = _users.end();
	for (; begin != end; ++begin)
		if (*begin == &user)
			break ;
	_users.erase(begin);
	delOperator(user);
	delSpeaker(user);
}

void	Channel::displayTopic(User &user)
{
	if (_topic.size() > 0)
		sendReply(user, RPL_TOPIC, _name, _topic, "", "");
	else
		sendReply(user, RPL_NOTOPIC, _name, "", "", "");
}
