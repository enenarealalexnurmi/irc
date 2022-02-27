/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:37:15 by enena             #+#    #+#             */
/*   Updated: 2022/02/27 15:05:26 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.hpp"

Nick::Nick(Message& msg, Server& owner, User* sender) :
	ACommand(msg, owner, sender){}

Nick::~Nick(){}

int	Nick::execute()
{
	if (this->_sender)
		this->_sender->setNickname(this->_base.getParams()[0]);
}
