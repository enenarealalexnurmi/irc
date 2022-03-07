/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NamesCmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:17:59 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:28:53 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NamesCmd.hpp"

NamesCmd::NamesCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
	_allowed = (this->_sender) && (this->_sender->getFlags() & REGISTERED);
}

NamesCmd::~NamesCmd(void){}

void	NamesCmd::whyNotAllowed(void) const
{
	throw Error(Error::ERR_NOTREGISTERED, this->_base);
}

void NamesCmd::execute(void)
{}