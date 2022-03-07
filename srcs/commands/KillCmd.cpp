/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KillCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:17:54 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:28:30 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "KillCmd.hpp"

KillCmd::KillCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
	_allowed = (this->_sender) && (this->_sender->getFlags() & REGISTERED);
}

KillCmd::~KillCmd(void){}

void	KillCmd::whyNotAllowed(void) const
{
	throw Error(Error::ERR_NOTREGISTERED, this->_base);
}

void KillCmd::execute(void)
{}