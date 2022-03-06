/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:37:15 by enena             #+#    #+#             */
/*   Updated: 2022/03/06 15:21:40 by enena            ###   ########.fr       */
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
		throw Error(Error::ERR_ERRONEUSNICKNAME, this->_base);
	std::string	spec = "`|^_-{}[]\\";
	for (size_t i = 0; i < nick.size(); i++)
	{
		if (!isalnum(nick[i]) || (spec.find(nick[i]) == std::string::npos))
			throw Error(Error::ERR_ERRONEUSNICKNAME, this->_base);
	}
	if (this->_owner->hasNickname(nick))
		throw Error(Error::ERR_NICKNAMEINUSE, this->_base);
}

void	NickCmd::execute(void)
{
	checkCountParam();
	std::string nick(this->_base.getParams()[0]);
	validateNickname(nick);
	if (this->_sender)
	{
		if (this->_sender->getFlags() & REGISTERED)
		{
			this->_owner->notifyUsersAbout(*(this->_sender),
				Message(":" + this->_sender->getPrefix() + " " + this->_base.getCommand() + " " + this->_base.getParams()[0] + "\n"));
		}
		this->_sender->setNickname(nick);
		this->_owner->checkRegistration(*(this->_sender));
	}
}
