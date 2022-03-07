/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NamesCmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:17:59 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 01:30:50 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NamesCmd.hpp"

NamesCmd::NamesCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
	_allowed = (this->_sender) && (this->_sender->getFlags() & REGISTERED);
}

NamesCmd::~NamesCmd(void){}

void	NamesCmd::whyNotAllowed(void) const
{
	throw Error(Error::ERR_NOTREGISTERED, this->_sender);
}

void NamesCmd::execute(void)
{
	if (this->_countParams == 0)
	{
		std::vector<std::string>	usersWithoutChannel;
		for (size_t i = 0; i < this->_owner->getConnectedUsers().size(); i++)
			usersWithoutChannel.push_back(this->_owner->getConnectedUsers()[i]->getNickname());
		std::map<std::string, Channel *>::const_iterator	it = this->_owner->getChannels().begin();
		std::map<std::string, Channel *>::const_iterator	ite = this->_owner->getChannels().end();
		for (; it != ite; ++ite)
		{
			if (!((*it).second->getFlags() & SECRET) && !((*it).second->getFlags() & PRIVATE))
			{
				(*it).second->printCreateInfo(*(this->_sender));
				for (size_t i = 0; i < usersWithoutChannel.size(); i++)
					if ((*it).second->isInChannel(usersWithoutChannel[i]))
						usersWithoutChannel.erase(usersWithoutChannel.begin() + i--);
			}
		}
		std::string	names;
		for (size_t i = 0; i < usersWithoutChannel.size(); i++)
		{
			names += usersWithoutChannel[i];
			if (i != (usersWithoutChannel.size() - 1))
				names += " ";
		}
		sendReply(*(this->_sender), RPL_NAMREPLY, "* *", names, "", "");
		sendReply(*(this->_sender), RPL_ENDOFNAMES, "*", "", "", "");
	}
	else
	{
		std::queue<std::string>	displayedChannels;
		displayedChannels = split(msg.getParams()[0], ',', false);
		while (displayedChannels.size() > 0)
		{
			try
			{
				Channel	*tmp = this->_owner->getChannels().at(displayedChannels.front());
				if (!(tmp->getFlags() & SECRET) && !(tmp->getFlags() & PRIVATE))
				{
					tmp->printCreateInfo(*(this->_sender));
					sendReply(*(this->_sender), RPL_ENDOFNAMES, tmp->getName(), "", "", ""s);
				}
			}
			catch(const std::exception& e)
			{}
			displayedChannels.pop();
		}
	}
}