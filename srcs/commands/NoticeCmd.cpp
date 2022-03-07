/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NoticeCmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:29:55 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:29:18 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NoticeCmd.hpp"

NoticeCmd::NoticeCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
	_allowed = (this->_sender) && (this->_sender->getFlags() & REGISTERED);
}

NoticeCmd::~NoticeCmd(void){}

void	NoticeCmd::whyNotAllowed(void) const
{
	throw Error(Error::ERR_NOTREGISTERED, this->_base);
}

void NoticeCmd::execute(void)
{}