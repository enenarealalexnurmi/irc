/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 02:33:47 by enena             #+#    #+#             */
/*   Updated: 2022/03/06 15:43:56 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserCmd.hpp"

UserCmd::UserCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 4;
}

UserCmd::~UserCmd(void){}

void	UserCmd::execute(void)
{
	checkCountParam();
	if (this->_sender)
	{
		if (this->_sender->getFlags() & REGISTERED)
			throw	Error(Error::ERR_ALREADYREGISTRED, this->_base);
		this->_sender->setUsername(this->_base.getParams()[0]);
		this->_sender->setRealname(this->_base.getParams()[0]);
	}
}
