/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopicCmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:26:56 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 08:22:26 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TopicCmd.hpp"

TopicCmd::TopicCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
	_allowed = (this->_sender) && (this->_sender->getFlags() & REGISTERED);
}

TopicCmd::~TopicCmd(void){}

void	TopicCmd::whyNotAllowed(void) const
{
	throw Error(Error::ERR_NOTREGISTERED, this->_sender);
}

void TopicCmd::execute(void)
{
	checkCountParam();
	std::string channelName;
	if (this->_sender)
	{
		if (!this->_owner->hasChannel(channelName) || this->_owner->getChannels()[channelName]->isInChannel(this->_sender->getNickname()))
			throw Error(Error::ERR_NOTONCHANNEL, this->_sender, this->_base.getParams()[0]);
		Channel* curChannel = this->_owner->getChannels()[channelName];
		if (this->_countParams < 2)
			curChannel->displayTopic(*(this->_sender));
		else
			curChannel->setTopic(*(this->_sender), this->_base.getParams()[1]);
	}
}