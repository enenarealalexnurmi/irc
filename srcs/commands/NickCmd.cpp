/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:37:15 by enena             #+#    #+#             */
/*   Updated: 2022/03/01 04:05:20 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NickCmd.hpp"

NickCmd::NickCmd(Message& msg, Server& owner, User* sender) :
	ACommand(msg, owner, sender){}

NickCmd::~NickCmd(){}

int	NickCmd::execute()
{
	if (this->_sender)
		this->_sender->setNickname(this->_base.getParams()[0]);
}
