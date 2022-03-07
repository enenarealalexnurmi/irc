/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:18:14 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:29:33 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PartCmd.hpp"

PartCmd::PartCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
	_allowed = (this->_sender) && (this->_sender->getFlags() & REGISTERED);
}

PartCmd::~PartCmd(void){}

void	PartCmd::whyNotAllowed(void) const
{
	throw Error(Error::ERR_NOTREGISTERED, this->_base);
}

void PartCmd::execute(void)
{}