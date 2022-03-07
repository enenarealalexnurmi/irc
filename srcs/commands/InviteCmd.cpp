/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:32:31 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 01:33:51 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InviteCmd.hpp"

InviteCmd::InviteCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 2;
	_allowed = (this->_sender) && (this->_sender->getFlags() & REGISTERED);
}

InviteCmd::~InviteCmd(void){}

void	InviteCmd::whyNotAllowed(void) const
{
	throw Error(Error::ERR_NOTREGISTERED, this->_sender);
}

void	InviteCmd::addToInvite(void)
{
	User	*receiver;
	for (size_t i = 0; i < connectedUsers.size(); ++i)
		if (this->_owner->getConnectedUsers()[i]->getNickname() == this->_base.getParams()[0])
			receiver = this->_owner->getConnectedUsers()[i];
	Channel	*chan = this->_owner->getChannels().at(this->_base.getParams()[1]);
	if (chan->containsNickname(this->_base.getParams()[0]))
		throw Error(Error::ERR_USERONCHANNEL, this->_sender, this->_base.getParams()[0], this->_owner->getServername());
	chan->addInvite(*(this->_sender), *receiver);
}

void	InviteCmd::execute(void)
{
	checkCountParam();
	if (!this->_owner->hasNickname(this->_base.getParams()[0]))
		throw Error(Error::ERR_NOSUCHNICK, this->_sender, this->_base.getParams()[0]);
	if (this->_sender)
	{
		if (!this->_sender->isOnChannel(this->_base.getParams()[1]) || !this->_owner->hasChannel(this->_base.getParams()[1]))
			throw Error(Error::ERR_NOTONCHANNEL, this->_sender, this->_base.getParams()[1]);
		addToInvite();
	}
}