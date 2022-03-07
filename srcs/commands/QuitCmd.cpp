/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 09:39:52 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:33:35 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "QuitCmd.hpp"

QuitCmd::QuitCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
	_allowed = true;
}

QuitCmd::~QuitCmd(void){}

void	QuitCmd::whyNotAllowed(void) const
{
	throw Error(Error::ERR_NOTREGISTERED, this->_base);
}

void QuitCmd::execute(void)
{
	if (this->_sender)
	{
		if (this->_countParams > 0)
			this->_sender->setExitMessage(this->_base.getParams()[0]);
		this->_sender->setFlag(BREAKCONNECTION);
	}
}