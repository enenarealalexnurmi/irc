/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VersionCmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:27:00 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 01:59:50 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VersionCmd.hpp"

VersionCmd::VersionCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
	_allowed = (this->_sender) && (this->_sender->getFlags() & REGISTERED);
}

VersionCmd::~VersionCmd(void){}

void	VersionCmd::whyNotAllowed(void) const
{
	throw Error(Error::ERR_NOTREGISTERED, this->_sender);
}

void VersionCmd::execute(void)
{
	if (this->_sender)
	{
		if (this->_base.getParams().size() > 0 && this->_base.getParams()[0] != this->_sender->getServername())
			throw Error(Error::ERR_NOSUCHSERVER, this->_sender, this->_base.getParams()[0]);
		sendReply(*(this->_sender), RPL_VERSION, this->_owner->getVersion(), this->_owner->getDebuglvl(), this->_owner->getServername(), this->_owner->getComments());
	}
}