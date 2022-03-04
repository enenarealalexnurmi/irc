/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 03:01:40 by enena             #+#    #+#             */
/*   Updated: 2022/03/04 07:49:58 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PingCmd.hpp"

PingCmd::PingCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender){}

PingCmd::~PingCmd(){}

int	PingCmd::execute()
{
    //if (!this->_base.getParams().empty())
		// throw error
	if (this->_sender)
		this->_sender->setPassword(this->_base.getParams()[0]);
	return 0;
}