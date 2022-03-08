/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:29:13 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 08:19:53 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JoinCmd.hpp"

JoinCmd::JoinCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
	_allowed = (this->_sender) && (this->_sender->getFlags() & REGISTERED);
}

JoinCmd::~JoinCmd(void){}

void	JoinCmd::whyNotAllowed(void) const
{
	throw Error(Error::ERR_NOTREGISTERED, this->_sender);
}

void	JoinCmd::validateChannelName(std::string channelName)
{
	if (!(channelName[0] == '&' || channelName[0] == '#'))
		throw Error(Error::ERR_NOSUCHCHANNEL, this->_sender, channelName);
	if (channelName.find_first_of(" ,") != std::string::npos || channelName.find(7) != std::string::npos)
		throw Error(Error::ERR_NOSUCHCHANNEL, this->_sender, channelName);
}

void	JoinCmd::connectToChannel(std::string channelName, std::string key)
{
	if (this->_sender)
	{
		try
		{
			Channel	*tmp = this->_owner->getChannels()[channelName];
			tmp->addConnect(*(this->_sender), key);
		}
		catch(const std::exception& e)
		{
			this->_owner->getChannels().insert(std::pair<std::string, Channel*>(channelName, new Channel(channelName, *(this->_sender), key)));
		}
		this->_sender->addChannel(*(this->_owner->getChannels()[channelName]));
	}
}

void	JoinCmd::execute(void)
{
	checkCountParam();
	this->_channels = split(this->_base.getParams()[0], ',', false);
	if (this->_countParams > 1)
		_keys = split(this->_base.getParams()[1], ',', false);
	for (; _channels.size() > 0; _channels.pop())
	{
		std::string	key = _keys.size() ? _keys.front() : "";
		if (_keys.size() > 0)
			_keys.pop();
		std::string curChannelName = _channels.front();
		validateChannelName(curChannelName);
		connectToChannel(curChannelName, key);
	}
}