/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopicCmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:26:56 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:36:57 by enena            ###   ########.fr       */
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
	throw Error(Error::ERR_NOTREGISTERED, this->_base);
}

void TopicCmd::execute(void)
{
	checkCountParam();
	std::string channelName;
	if (this->_sender)
	{
		if (!this->_owner->hasChannel(channelName) || this->_owner->getChannels().at(channelName)->isInChannel(*(this->_sender)))
			throw Error(Error::ERR_NOTONCHANNEL, this->_base);
		Channel* curChannel = this->_owner->getChannels().at(channelName);
		if (this->_countParams < 2)
			curChannel->displayTopic(*(this->_sender));
		else
			curChannel->setTopic(*(this->_sender), this->_base.getParams()[1]);
	}
}