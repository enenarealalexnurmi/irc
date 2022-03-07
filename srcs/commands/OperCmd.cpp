/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:29:20 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 01:58:06 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperCmd.hpp"

OperCmd::OperCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 2;
	_allowed = (this->_sender) && (this->_sender->getFlags() & REGISTERED);
}

OperCmd::~OperCmd(void){}

void	OperCmd::whyNotAllowed(void) const
{
	throw Error(Error::ERR_NOTREGISTERED, this->_sender);
}

void OperCmd::execute(void)
{
	checkCountParam();
	if (this->_sender)
	{
		if (this->_owner->isPrivilegedOperator(this->_base.getParams()[0], this->_base.getParams()[1]))
		{
			this->_sender->setFlag(IRCOPERATOR);
			sendReply(*(this->_sender), RPL_YOUREOPER, "", "", "", "");
		}
		else
			throw Error(Error::ERR_PASSWDMISMATCH, this->_sender);
	}
}