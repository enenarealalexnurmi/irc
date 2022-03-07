/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:17:55 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:28:37 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ListCmd.hpp"

ListCmd::ListCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
	_allowed = (this->_sender) && (this->_sender->getFlags() & REGISTERED);
}

ListCmd::~ListCmd(void){}

void	ListCmd::whyNotAllowed(void) const
{
	throw Error(Error::ERR_NOTREGISTERED, this->_base);
}

void ListCmd::execute(void)
{}