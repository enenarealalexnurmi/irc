/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivmsgCmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 04:19:40 by enena             #+#    #+#             */
/*   Updated: 2022/03/04 07:34:44 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PrivmsgCmd.hpp"

PrivmsgCmd::PrivmsgCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender){}

PrivmsgCmd::~PrivmsgCmd(){}

int	PrivmsgCmd::execute()
{
	if (this->_sender)
		this->_sender->setPassword(this->_base.getParams()[0]);
	return 0;
}