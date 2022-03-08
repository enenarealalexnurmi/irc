/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:18:14 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 08:22:52 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PartCmd.hpp"

PartCmd::PartCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
	_allowed = (this->_sender) && (this->_sender->getFlags() & REGISTERED);
}

PartCmd::~PartCmd(void){}

void	PartCmd::whyNotAllowed(void) const
{
	throw Error(Error::ERR_NOTREGISTERED, this->_sender);
}

void PartCmd::execute(void)
{
	checkCountParam();
	std::queue<std::string>	channels = split(this->_base.getParams()[0], ',', false);
	while (channels.size() > 0)
	{
		if (!this->_owner->hasChannel(channels.front()))
			throw Error(Error::ERR_NOSUCHCHANNEL, this->_sender, channels.front());
		if (!this->_sender->isOnChannel(channels.front()))
			throw Error(Error::ERR_NOTONCHANNEL, this->_sender, channels.front());
		this->_owner->getChannels()[channels.front()]->sendMessage("PART " + channels.front() + "\n", *(this->_sender), true);
		this->_owner->getChannels()[channels.front()]->delConnect(*(this->_sender));
		this->_sender->removeChannel(channels.front());
		channels.pop();
	}
}