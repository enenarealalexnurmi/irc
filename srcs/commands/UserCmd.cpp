/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 02:33:47 by enena             #+#    #+#             */
/*   Updated: 2022/03/03 23:37:42 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/commands/UserCmd.hpp"

UserCmd::UserCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender){}

UserCmd::~UserCmd(){}

int	UserCmd::execute()
{
	if (this->_sender)
		this->_sender->setNickname(this->_base.getParams()[0]);
	return 0;
}
