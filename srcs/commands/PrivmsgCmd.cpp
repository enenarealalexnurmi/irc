/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivmsgCmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 04:19:40 by enena             #+#    #+#             */
/*   Updated: 2022/03/06 19:20:34 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PrivmsgCmd.hpp"

PrivmsgCmd::PrivmsgCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender){}

PrivmsgCmd::~PrivmsgCmd(void){}

void	PrivmsgCmd::execute(void)
{
	if (this->_base.getParams().size() == 0)
		throw Error(Error::ERR_NORECIPIENT, this->_base);
	if (this->_base.getParams().size() == 1)
		throw Error(Error::ERR_NOTEXTTOSEND, this->_base);
	std::queue<std::string> receivers = split(this->_base.getParams()[0], ',', false);
	
}