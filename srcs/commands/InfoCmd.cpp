/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InfoCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:17:48 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 23:57:22 by enena            ###   ########.fr       */
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
	throw Error(Error::ERR_NOTREGISTERED, this->_base);
}

void	InfoCmd::execute(void)
{
	if (this->_sender)
	{
		std::vector<std::string>::iterator ite = this->_owner->getInfo().end();
		for (std::vector<std::string>::iterator it = this->_owner->getInfo().begin(); it < ite; it++)
			Message(*it).sendIt(this->_sender->getSockfd());
	}
}