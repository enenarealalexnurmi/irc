/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivmsgCmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 04:19:40 by enena             #+#    #+#             */
/*   Updated: 2022/03/04 23:11:41 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PrivmsgCmd.hpp"

PrivmsgCmd::PrivmsgCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender){}

PrivmsgCmd::~PrivmsgCmd(void){}

void	PrivmsgCmd::execute(void)
{
	if (this->_sender)
		this->_sender->setPassword(this->_base.getParams()[0]);
}