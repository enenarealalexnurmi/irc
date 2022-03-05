/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 02:33:06 by enena             #+#    #+#             */
/*   Updated: 2022/03/04 23:11:03 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PassCmd.hpp"

PassCmd::PassCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender){}

PassCmd::~PassCmd(void){}

void	PassCmd::execute(void)
{
	//if (!this->_base.getParams().empty())
		// throw error
	if (this->_sender)
		this->_sender->setPassword(this->_base.getParams()[0]);
}
