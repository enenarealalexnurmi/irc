/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivmsgNoticeCmd.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 04:19:40 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 02:36:42 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PrivmsgNoticeCmd.hpp"

PrivmsgNoticeCmd::PrivmsgNoticeCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
	_allowed = (this->_sender) && (this->_sender->getFlags() & REGISTERED);
}

PrivmsgNoticeCmd::~PrivmsgNoticeCmd(void){}

void	PrivmsgNoticeCmd::whyNotAllowed(void) const
{
	throw Error(Error::ERR_NOTREGISTERED, this->_sender);
}

void	PrivmsgNoticeCmd::execute(void)
{
	if (this->_countParams == 0)
		throw Error(Error::ERR_NORECIPIENT, this->_sender, this->_base.getCommand());
	if (this->_countParams == 1)
		throw Error(Error::ERR_NOTEXTTOSEND, this->_sender);
	std::queue<std::string> receivers = split(this->_base.getParams()[0], ',', false);
	std::set<std::string> uniqReceivers;
	if (this->_base.getCommand() == "NOTICE" && (receivers.size() > 1 \
	|| receivers.front()[0] == '#' || receivers.front()[0] == '&'))
		throw Error(Error::ERR_NOSUCHNICK, this->_sender, this->_base.getParams()[0]);
	while (receivers.size() > 0)
	{
		if (uniqReceivers.find(receivers.front()) != uniqReceivers.end())
			throw Error(Error::ERR_TOOMANYTARGETS, this->_sender, receivers.front());
		if (receivers.front()[0] == '#' || receivers.front()[0] == '&')
		{
			if (!this->_owner->hasChannel(receivers.front()))
				throw Error(Error::ERR_NOSUCHNICK, this->_sender, receivers.front());
			if (!this->_owner->getChannels()[receivers.front()]->isInChannel(this->_sender->getNickname()))
				throw Error(Error::ERR_CANNOTSENDTOCHAN, this->_sender, receivers.front());
		}
		else if (!this->_owner->hasNickname(receivers.front()))
			throw Error(Error::ERR_NOSUCHNICK, this->_sender, this->_base.getParams()[0]);
		uniqReceivers.insert(receivers.front());
		receivers.pop();
	}
	for (std::set<std::string>::iterator it = uniqReceivers.begin(); it != uniqReceivers.end(); ++it)
	{
		if ((*it)[0] == '#' || (*it)[0] == '&')
		{
			Channel *receiverChannel = this->_owner->getChannels()[*it];
			if (receiverChannel->getFlags() & MODERATED && (!receiverChannel->isOperator(*(this->_sender)) && !receiverChannel->isSpeaker(*(this->_sender))))
				throw Error(Error::ERR_CANNOTSENDTOCHAN, this->_sender, *it);
			else
				receiverChannel->sendMessage(this->_base.getCommand() + " " + *it + " :" + this->_base.getParams()[1] + "\n", *(this->_sender), false);
		}
		else
		{
			if (this->_base.getCommand() == "PRIVMSG" && (this->_owner->getUserByName(*it)->getFlags() & AWAY))
				sendReply(*(this->_sender), RPL_AWAY, *it, this->_owner->getUserByName(*it)->getAwayMessage(), "", "");
			if (this->_base.getCommand() != "NOTICE" || (this->_owner->getUserByName(*it)->getFlags() & RECEIVENOTICE))
				this->_owner->getUserByName(*it)->sendMessage(":" + this->_sender->getPrefix() + " " + this->_base.getCommand() + " " + *it + " :" + this->_base.getParams()[1] + "\n");
		}
	}
}