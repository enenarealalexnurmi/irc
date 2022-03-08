/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:37:15 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 04:42:53 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NickCmd.hpp"

NickCmd::NickCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
	_allowed = true;
}

NickCmd::~NickCmd(void){}

void	NickCmd::whyNotAllowed(void) const
{
	throw Error(Error::ERR_NOTREGISTERED, this->_sender);
}

void	NickCmd::validateNickname(const std::string& nick)
{
	if (nick.length() > 9)
		throw Error(Error::ERR_ERRONEUSNICKNAME, this->_sender, this->_base.getParams()[0]);
	std::string	spec = "`|^_-{}[]\\";
	for (size_t i = 0; i < nick.size(); i++)
	{
		if (!isalnum(nick[i]) || (spec.find(nick[i]) != std::string::npos))
			throw Error(Error::ERR_ERRONEUSNICKNAME, this->_sender, this->_base.getParams()[0]);
	}
	if (this->_owner->hasNickname(nick))
		throw Error(Error::ERR_NICKNAMEINUSE, this->_sender, this->_base.getParams()[0]);
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
