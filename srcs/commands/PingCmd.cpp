/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 03:01:40 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 01:45:42 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PingCmd.hpp"

PingCmd::PingCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
	_allowed = (this->_sender) && (this->_sender->getFlags() & REGISTERED);
}

PingCmd::~PingCmd(void){}

void	PingCmd::whyNotAllowed(void) const
{
	throw Error(Error::ERR_NOTREGISTERED, this->_sender);
}

void PingCmd::execute(void)
{
	if (this->_base.getParams().empty())
		throw Error(Error::ERR_NOORIGIN, this->_sender);
	if (this->_sender)
		Message(":" + this->_owner->getServername() + " PONG :" + this->_base.getParams()[0]).sendIt(this->_sender->getSockfd());
}