/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InfoCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskeleto <mskeleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:17:48 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 06:00:05 by mskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InfoCmd.hpp"

InfoCmd::InfoCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
	_allowed = (this->_sender) && (this->_sender->getFlags() & REGISTERED);
}

InfoCmd::~InfoCmd(void){}

void	InfoCmd::whyNotAllowed(void) const
{
	throw Error(Error::ERR_NOTREGISTERED, this->_sender);
}

void	InfoCmd::execute(void)
{
	if (this->_sender)
	{
		for (size_t it = 0; it < this->_owner->getInfo().size(); it++)
			Message(this->_owner->getInfo()[it] + "\n").sendIt(this->_sender->getSockfd());
	}
}