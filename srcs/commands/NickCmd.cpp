/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:37:15 by enena             #+#    #+#             */
/*   Updated: 2022/03/03 23:37:33 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NickCmd.hpp"

NickCmd::NickCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender){}

NickCmd::~NickCmd(){}

int	NickCmd::execute()
{
	if (!this->_base.getParams().empty())
	if (this->_sender)
		this->_sender->setNickname(this->_base.getParams()[0]);
	return 0;
}
