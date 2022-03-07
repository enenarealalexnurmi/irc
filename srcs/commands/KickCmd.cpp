/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:35:06 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 23:12:43 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "KickCmd.hpp"

KickCmd::KickCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 2;
	_allowed = (this->_sender) && (this->_sender->getFlags() & REGISTERED);
}

KickCmd::~KickCmd(void){}

void	KickCmd::whyNotAllowed(void) const
{
	throw Error(Error::ERR_NOTREGISTERED, this->_base);
}

void KickCmd::execute(void)
{
	checkCountParam();
	if (!this->_owner->hasChannel(this->_base.getParams()[0]))
		throw Error(Error::ERR_NOSUCHCHANNEL, this->_base);
	if (this->_sender)
	{
		Channel	*channel = this->_owner->getChannels().at(this->_base.getParams()[0]);
		if (!channel->isOperator(*(this->_sender)))
			throw Error(Error::ERR_CHANOPRIVSNEEDED, this->_base);
		if (!channel->isInChannel(this->_sender->getNickname()))
			throw Error(Error::ERR_NOTONCHANNEL, this->_base);
		if (!this->_owner->hasNickname(this->_base.getParams()[1]))
			throw Error(Error::ERR_NOSUCHNICK, this->_base);
		if (!channel->isInChannel(this->_base.getParams()[1]))
			throw Error(Error::ERR_USERNOTINCHANNEL, this->_base);
		std::string	message = "KICK " + channel->getName() + " " + this->_base.getParams()[1] + " :";
		if (this->_base.getParams().size() > 2)
			message += this->_base.getParams()[2];
		else
			message += this->_sender->getNickname();
		channel->sendMessage(message + "\n", *(this->_sender), true);
		channel->delConnect(*(this->_owner->getUserByName(this->_base.getParams()[1])));
		this->_owner->getUserByName(this->_base.getParams()[1])->removeChannel(this->_base.getParams()[0]);
	}
}