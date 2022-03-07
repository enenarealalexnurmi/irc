/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 02:33:06 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:29:41 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PassCmd.hpp"

PassCmd::PassCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
	_allowed = true;
}

PassCmd::~PassCmd(void){}

void	PassCmd::whyNotAllowed(void) const
{
	throw Error(Error::ERR_NOTREGISTERED, this->_base);
}

void	PassCmd::execute(void)
{
	checkCountParam();
	if (this->_sender)
		this->_sender->setPassword(this->_base.getParams()[0]);
	if (this->_sender)
	{
		if (this->_sender->getFlags() & REGISTERED)
			throw	Error(Error::ERR_ALREADYREGISTRED, this->_base);
		this->_sender->setPassword(this->_base.getParams()[0]);
	}
	
}
