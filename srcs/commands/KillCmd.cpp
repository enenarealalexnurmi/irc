/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KillCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:17:54 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 01:50:40 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "KillCmd.hpp"

KillCmd::KillCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
	_allowed = (this->_sender) && (this->_sender->getFlags() & REGISTERED) && (this->_sender->getFlags() & IRCOPERATOR);
}

KillCmd::~KillCmd(void){}

void	KillCmd::whyNotAllowed(void) const
{
	if (this->_sender)
	{
		if (!this->_sender->getFlags() & REGISTERED)
			throw Error(Error::ERR_NOTREGISTERED, this->_sender);
		if (!this->_sender->getFlags() & IRCOPERATOR)
			throw Error(Error::ERR_NOPRIVILEGES, this->_sender);
	}
}

void KillCmd::execute(void)
{
	string username = this->_base.getParams()[0];
	if (username == this->_owner->getServername())
		throw Error(Error::ERR_CANTKILLSERVER, this->_sender);	
	if (!this->_owner->hasNickname(username))
		throw Error(Error::ERR_NOSUCHNICK, this->_sender, this->_base.getParams()[0]);
	User *userToKill = this->_owner->getUserByName(username);	
	userToKill->sendMessage(this->_base.getParams()[1] + "\n");
	userToKill->setFlag(BREAKCONNECTION);
}