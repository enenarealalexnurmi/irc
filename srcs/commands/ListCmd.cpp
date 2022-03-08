/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:17:55 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 08:24:35 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ListCmd.hpp"

ListCmd::ListCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
	_allowed = (this->_sender) && (this->_sender->getFlags() & REGISTERED);
}

ListCmd::~ListCmd(void){}

void	ListCmd::whyNotAllowed(void) const
{
	throw Error(Error::ERR_NOTREGISTERED, this->_sender);
}

void ListCmd::execute(void)
{
	if (this->_countParams > 1 && this->_base.getParams()[1] != this->_sender->getServername())
		throw Error(Error::ERR_NOSUCHSERVER, this->_sender, this->_base.getParams()[1]);
	std::queue<std::string>		channels;
	std::vector<std::string>	displayedChannels;
	if (this->_countParams > 0)
	{
		channels = split(this->_base.getParams()[0], ',', false);
		while (channels.size() > 0)
		{
			if (this->_owner->hasChannel(channels.front()))
				displayedChannels.push_back(channels.front());
			channels.pop();
		}
	}
	else
	{
		std::map<std::string, Channel *>::const_iterator	it = this->_owner->getChannels().begin();
		std::map<std::string, Channel *>::const_iterator	ite = this->_owner->getChannels().end();
		for (; it != ite; ++it)
			displayedChannels.push_back((*it).first);
	}
	sendReply(*(this->_sender), RPL_LISTSTART, "", "", "", "");
	for (size_t i = 0; i < displayedChannels.size(); ++i)
		this->_owner->getChannels()[displayedChannels[i]]->printChannelInfo(*(this->_sender));
	sendReply(*(this->_sender), RPL_LISTEND, "", "", "", "");
}