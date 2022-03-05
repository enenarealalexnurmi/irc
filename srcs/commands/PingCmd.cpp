/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 03:01:40 by enena             #+#    #+#             */
/*   Updated: 2022/03/04 23:11:10 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PingCmd.hpp"

PingCmd::PingCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender){}

PingCmd::~PingCmd(void){}

void PingCmd::execute(void)
{
	//if (!this->_base.getParams().empty())
		// throw error
	if (this->_sender)
		this->_sender->setPassword(this->_base.getParams()[0]);
}