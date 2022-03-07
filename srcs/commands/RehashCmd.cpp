/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RehashCmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:26:49 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 23:50:48 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RehashCmd.hpp"

RehashCmd::RehashCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
	_allowed = (this->_sender) && (this->_sender->getFlags() & REGISTERED) && (this->_sender->getFlags() & IRCOPERATOR);
}

RehashCmd::~RehashCmd(void){}

void	RehashCmd::whyNotAllowed(void) const
{
	if (this->_sender)
	{
		if (!this->_sender->getFlags() & REGISTERED)
			throw Error(Error::ERR_NOTREGISTERED, this->_base);
		if (!this->_sender->getFlags() & IRCOPERATOR)
			throw Error(Error::ERR_NOPRIVILEGES, this->_base);
	}
}

void RehashCmd::execute(void)
{
	this->_owner->rereadConfig();
	if (this->_sender)
	{
		sendReply(*(this->_sender), RPL_REHASHING, "", "", "", "");
	}
}