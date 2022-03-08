/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:17:57 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 03:42:04 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ModeCmd.hpp"

ModeCmd::ModeCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender)
{
	_reqCountParam = 1;
	_allowed = (this->_sender) && (this->_sender->getFlags() & REGISTERED);
}

ModeCmd::~ModeCmd(void){}

void	ModeCmd::whyNotAllowed(void) const
{
	throw Error(Error::ERR_NOTREGISTERED, this->_sender);
}

void	ModeCmd::setFlagModeChannel(const Message &msg, User* user)
{
	std::string	channelName = msg.getParams()[0];
	std::string	flag = msg.getParams()[1];
	if (flag == "+o")
	{
		if (this->_countParams < 3)
			throw Error(Error::ERR_NEEDMOREPARAMS, user, msg.getCommand());
		else if (!this->_owner->hasNickname(msg.getParams()[2]))
			throw Error(Error::ERR_NOSUCHNICK, user, msg.getParams()[2]);
		else
			this->_owner->getChannels()[channelName]->addOperator(*(this->_owner->getUserByName(msg.getParams()[2])));
	}
	else if (flag == "-o")
	{
		if (this->_countParams < 3)
			throw Error(Error::ERR_NEEDMOREPARAMS, user, msg.getCommand());
		else if (!this->_owner->hasNickname(msg.getParams()[2]))
			throw Error(Error::ERR_NOSUCHNICK, user, msg.getParams()[2]);
		else
			this->_owner->getChannels()[channelName]->delOperator(*(this->_owner->getUserByName(msg.getParams()[2])));
	}
	else if (flag == "+p")
		this->_owner->getChannels()[channelName]->addFlag(PRIVATE);
	else if (flag == "-p")
		this->_owner->getChannels()[channelName]->delFlag(PRIVATE);
	else if (flag == "+s")
		this->_owner->getChannels()[channelName]->addFlag(SECRET);
	else if (flag == "-s")
		this->_owner->getChannels()[channelName]->delFlag(SECRET);
	else if (flag == "+i")
		this->_owner->getChannels()[channelName]->addFlag(INVITEONLY);
	else if (flag == "-i")
		this->_owner->getChannels()[channelName]->delFlag(INVITEONLY);
	else if (flag == "+t")
		this->_owner->getChannels()[channelName]->addFlag(TOPICSET);
	else if (flag == "-t")
		this->_owner->getChannels()[channelName]->delFlag(TOPICSET);
	else if (flag == "+n")
	{}
	else if (flag == "-n")
	{}
	else if (flag == "+m")
		this->_owner->getChannels()[channelName]->addFlag(MODERATED);
	else if (flag == "-m")
		this->_owner->getChannels()[channelName]->delFlag(MODERATED);
	else if (flag == "+l")
	{
		if (this->_countParams < 3)
			throw Error(Error::ERR_NEEDMOREPARAMS, user, msg.getCommand());
		this->_owner->getChannels()[channelName]->setLimit(atoi(msg.getParams()[2].c_str()));
	}
	else if (flag == "-l")
	{
		if (this->_countParams < 3)
			throw Error(Error::ERR_NEEDMOREPARAMS, user, msg.getCommand());
		this->_owner->getChannels()[channelName]->setLimit(0);
	}
	else if (flag == "+b")
	{
		if (this->_countParams < 3)
			throw Error(Error::ERR_NEEDMOREPARAMS, user, msg.getCommand());
		this->_owner->getChannels()[channelName]->addBanMasks(msg.getParams()[2]);
	}
	else if (flag == "-b")
	{
		if (this->_countParams < 3)
			throw Error(Error::ERR_NEEDMOREPARAMS, user, msg.getCommand());
		this->_owner->getChannels()[channelName]->delBanMasks(msg.getParams()[2]);
	}
	else if (flag == "+v")
	{
		if (this->_countParams < 3)
			throw Error(Error::ERR_NEEDMOREPARAMS, user, msg.getCommand());
		if (!this->_owner->hasNickname(msg.getParams()[2]))
			throw Error(Error::ERR_NOSUCHNICK, user, msg.getParams()[2]);
		this->_owner->getChannels()[channelName]->addSpeaker(*(this->_owner->getUserByName(msg.getParams()[2])));
	}
	else if (flag == "-v")
	{
		if (this->_countParams < 3)
			throw Error(Error::ERR_NEEDMOREPARAMS, user, msg.getCommand());
		if (!this->_owner->hasNickname(msg.getParams()[2]))
			throw Error(Error::ERR_NOSUCHNICK, user, msg.getParams()[2]);
		this->_owner->getChannels()[channelName]->delSpeaker(*(this->_owner->getUserByName(msg.getParams()[2])));
	}
	else if (flag == "+k")
	{
		if (this->_countParams < 3)
			throw Error(Error::ERR_NEEDMOREPARAMS, user, msg.getCommand());
		this->_owner->getChannels()[channelName]->setPass(*(this->_sender), msg.getParams()[2]);
	}
	else if (flag == "-k")
	{
		if (this->_countParams < 3)
			throw Error(Error::ERR_NEEDMOREPARAMS, user, msg.getCommand());
		else
			this->_owner->getChannels()[channelName]->setPass(*(this->_sender), "");
	}
	else
		throw Error(Error::ERR_UNKNOWNMODE, user, msg.getCommand());
}

void	ModeCmd::setFlagModeUser(const std::string& flag, User* user)
{
	if (flag == "+i")
		user->setFlag(INVISIBLE);
	else if (flag == "-i")
		user->delFlag(INVISIBLE);
	else if (flag == "+s")
		user->setFlag(RECEIVENOTICE);
	else if (flag == "-s")
		user->delFlag(RECEIVENOTICE);
	else if (flag == "+w")
		user->setFlag(RECEIVEWALLOPS);
	else if (flag == "-w")
		user->delFlag(RECEIVEWALLOPS);
	else if (flag == "+o")
	{}
	else if (flag == "-o")
		user->delFlag(IRCOPERATOR);
	else
		throw Error(Error::ERR_UMODEUNKNOWNFLAG, this->_sender);
}

void	ModeCmd::execute(void)
{
	checkCountParam();
	if (this->_sender)
	{
		if (this->_base.getParams()[0][0] == '#')
		{
			if (!this->_owner->hasChannel(this->_base.getParams()[0]))
				throw Error(Error::ERR_NOSUCHCHANNEL, this->_sender, this->_base.getParams()[0]);
			if (!this->_owner->getChannels().at(this->_base.getParams()[0])->isOperator(*(this->_sender)))
				throw Error(Error::ERR_CHANOPRIVSNEEDED, this->_sender, this->_base.getParams()[0]);
			if (!this->_owner->getChannels().at(this->_base.getParams()[0])->isInChannel(this->_sender->getNickname()))
				throw Error(Error::ERR_NOTONCHANNEL, this->_sender, this->_base.getParams()[0]);
			if (this->_base.getParams().size() == 1)
				sendReply(*(this->_sender), RPL_CHANNELMODEIS, this->_base.getParams()[0], this->_owner->getChannels().at(this->_base.getParams()[0])->printFlag(), "", "");
			else
			{
				setFlagModeChannel(this->_base, this->_sender);
				std::string	flag = this->_base.getParams()[1];
				std::string	tmp = (flag[1] == 'o' || flag[1] == 'v') ? " " + this->_base.getParams()[2] : "";
				this->_owner->getChannels().at(this->_base.getParams()[0])->sendMessage("MODE " + this->_base.getParams()[0] + " " + this->_base.getParams()[1]  + tmp + "\n", *(this->_sender), true);
			}
		}
		else
		{
			if (this->_base.getParams()[0] != this->_sender->getNickname())
				throw Error(Error::ERR_USERSDONTMATCH, this->_sender);
			else
			{
				if (this->_countParams == 1)
				{
					std::string	flags = "+";
					if (this->_sender->getFlags() & INVISIBLE)
						flags += "i";
					if (this->_sender->getFlags() & RECEIVENOTICE)
						flags += "s";
					if (this->_sender->getFlags() & RECEIVEWALLOPS)
						flags += "w";
					if (this->_sender->getFlags() & IRCOPERATOR)
						flags += "o";
					sendReply(*(this->_sender), RPL_UMODEIS, flags, "", "", "");
				}
				else 
				{
					setFlagModeUser(this->_base.getParams()[1], this->_sender);
					this->_sender->sendMessage(":" + this->_sender->getPrefix() + " MODE " + this->_base.getParams()[0] + " " + this->_base.getParams()[1] + "\n");
				}
			}
		}
	}
}