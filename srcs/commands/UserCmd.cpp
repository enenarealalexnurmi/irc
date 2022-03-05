/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 02:33:47 by enena             #+#    #+#             */
/*   Updated: 2022/03/04 23:12:47 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserCmd.hpp"

UserCmd::UserCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender){}

UserCmd::~UserCmd(void){}

void	UserCmd::execute(void)
{
	//if (!this->_base.getParams().empty())
		// throw error
	if (this->_sender)
	{
		this->_sender->setUsername(this->_base.getParams()[0]);
		this->_sender->setRealname(this->_base.getParams()[0]);
	}
}
