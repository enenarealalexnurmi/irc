/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PongCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 03:01:49 by enena             #+#    #+#             */
/*   Updated: 2022/03/06 17:36:23 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PongCmd.hpp"

PongCmd::PongCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
}

PongCmd::~PongCmd(void){}

void	PongCmd::execute(void)
{
	if (this->_base.getParams().empty())
		throw Error(Error::ERR_NOSUCHSERVER, this->_base);
	if (this->_base.getParams()[0] != this->_owner->getServername())
		throw Error(Error::ERR_NOSUCHSERVER, this->_base);
	if (this->_sender)
		this->_sender->removeFlag(PINGING);
}