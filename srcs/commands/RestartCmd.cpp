/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RestartCmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:26:53 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 01:43:15 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RestartCmd.hpp"

RestartCmd::RestartCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
	_allowed = (this->_sender) && (this->_sender->getFlags() & REGISTERED) && (this->_sender->getFlags() & IRCOPERATOR);
}

RestartCmd::~RestartCmd(void){}

void	RestartCmd::whyNotAllowed(void) const
{
	if (this->_sender)
	{
		if (!this->_sender->getFlags() & REGISTERED)
			throw Error(Error::ERR_NOTREGISTERED, this->_sender);
		if (!this->_sender->getFlags() & IRCOPERATOR)
			throw Error(Error::ERR_NOPRIVILEGES, this->_sender);
	}
}

void RestartCmd::execute(void)
{
	std::vector<User *>::iterator it = this->_owner->getConnectedUsers().begin();
	std::vector<User *>::iterator ite = this->_owner->getConnectedUsers().end();
	for (; it != ite; it++) 
		(*it)->setFlag(BREAKCONNECTION);
	this->_owner->rereadConfig();
	close(this->_owner->getSockfd());
	this->_owner->serverMagic();
}