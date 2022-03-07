/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PongCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 03:01:49 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 01:45:31 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PongCmd.hpp"

PongCmd::PongCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
	_allowed = (this->_sender) && (this->_sender->getFlags() & REGISTERED);
}

PongCmd::~PongCmd(void){}

void	PongCmd::whyNotAllowed(void) const
{
	throw Error(Error::ERR_NOTREGISTERED, this->_sender);
}

void	PongCmd::execute(void)
{
	std::string ret = this->_base.getParams().size() > 0 ? this->_base.getParams()[0] : "";
	if (this->_base.getParams().empty())
		throw Error(Error::ERR_NOSUCHSERVER, this->_sender, ret);
	if (this->_base.getParams()[0] != this->_owner->getServername())
		throw Error(Error::ERR_NOSUCHSERVER, this->_sender, ret);
	if (this->_sender)
		this->_sender->removeFlag(PINGING);
}