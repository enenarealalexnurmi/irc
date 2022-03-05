/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:37:15 by enena             #+#    #+#             */
/*   Updated: 2022/03/05 00:11:54 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NickCmd.hpp"

NickCmd::NickCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
}

NickCmd::~NickCmd(void){}

void	NickCmd::validateNickname(const std::string& nick)
{
	if (nick.length() > 9)
		throw Error(Error::ERR_ERRONEUSNICKNAME, *this);
	std::string	spec = "-[]\\`^{}";
	for (size_t i = 0; i < nick.size(); i++)
	{
		if (!isalnum(nick[i]) || (spec.find(nick[i]) == std::string::npos))
			throw Error(Error::ERR_ERRONEUSNICKNAME, *this);
	}
	if (this->_owner->hasNickname(nick))
		throw Error(Error::ERR_NICKNAMEINUSE, *this);
}

void	NickCmd::execute(void)
{
	checkCountParam();
	std::string nick(this->_base.getParams()[0]);
	validateNickname(nick);
	if (this->_sender)
		this->_sender->setNickname(nick);
}
