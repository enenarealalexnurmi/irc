/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 12:21:46 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 09:46:29 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandFactory.hpp"
#include "QuitCmd.hpp"
#include "PassCmd.hpp"
#include "NickCmd.hpp"
#include "UserCmd.hpp"
#include "PrivmsgNoticeCmd.hpp"
#include "JoinCmd.hpp"
#include "PartCmd.hpp"
#include "ModeCmd.hpp"
#include "TopicCmd.hpp"
#include "ListCmd.hpp"
#include "InviteCmd.hpp"
#include "KickCmd.hpp"
#include "OperCmd.hpp"
#include "KillCmd.hpp"
#include "RehashCmd.hpp"
#include "PingCmd.hpp"
#include "PongCmd.hpp"
#include "VersionCmd.hpp"
#include "InfoCmd.hpp"

CommandFactory::CommandFactory(Server* owner) : 
	_owner(owner)
{
	this->dict.insert(valueDict(std::string("QUIT"), &CommandFactory::createQuit));
	this->dict.insert(valueDict(std::string("PASS"), &CommandFactory::createPass));
	this->dict.insert(valueDict(std::string("NICK"), &CommandFactory::createNick));
	this->dict.insert(valueDict(std::string("USER"), &CommandFactory::createUser));
	this->dict.insert(valueDict(std::string("PRIVMSG"), &CommandFactory::createPrivmsgNotice));
	this->dict.insert(valueDict(std::string("NOTICE"), &CommandFactory::createPrivmsgNotice));
	this->dict.insert(valueDict(std::string("JOIN"), &CommandFactory::createJoin));
	this->dict.insert(valueDict(std::string("PART"), &CommandFactory::createPart));
	this->dict.insert(valueDict(std::string("MODE"), &CommandFactory::createMode));
	this->dict.insert(valueDict(std::string("TOPIC"), &CommandFactory::createTopic));
	this->dict.insert(valueDict(std::string("LIST"), &CommandFactory::createList));
	this->dict.insert(valueDict(std::string("INVITE"), &CommandFactory::createInvite));
	this->dict.insert(valueDict(std::string("KICK"), &CommandFactory::createKick));
	this->dict.insert(valueDict(std::string("OPER"), &CommandFactory::createOper));
	this->dict.insert(valueDict(std::string("KILL"), &CommandFactory::createKill));
	this->dict.insert(valueDict(std::string("REHASH"), &CommandFactory::createRehash));
	this->dict.insert(valueDict(std::string("PING"), &CommandFactory::createPing));
	this->dict.insert(valueDict(std::string("PONG"), &CommandFactory::createPong));
	this->dict.insert(valueDict(std::string("VERSION"), &CommandFactory::createVersion));
	this->dict.insert(valueDict(std::string("INFO"), &CommandFactory::createInfo));
}

CommandFactory::~CommandFactory()
{
}

ACommand*	CommandFactory::createCommand(Message& msg, User* sender)
{
	ACommand* ret;
	try
	{
		ret = (this->*(dict.at(msg.getCommand())))(msg, sender);
	}
	catch(const std::exception& e)
	{
		throw Error(Error::ERR_UNKNOWNCOMMAND, sender, msg.getCommand());
	}
	return ret;
}

ACommand*	CommandFactory::createQuit(Message& msg, User* sender)
{
	return (new QuitCmd(msg, this->_owner, sender));
}

ACommand*	CommandFactory::createPass(Message& msg, User* sender)
{
	return (new PassCmd(msg, this->_owner, sender));
}

ACommand*	CommandFactory::createNick(Message& msg, User* sender)
{
	return (new NickCmd(msg, this->_owner, sender));
}

ACommand*	CommandFactory::createUser(Message& msg, User* sender)
{
	return (new UserCmd(msg, this->_owner, sender));
}

ACommand*	CommandFactory::createPrivmsgNotice(Message& msg, User* sender)
{
	return (new PrivmsgNoticeCmd(msg, this->_owner, sender));
}

ACommand*	CommandFactory::createJoin(Message& msg, User* sender)
{
	return (new JoinCmd(msg, this->_owner, sender));
}

ACommand*	CommandFactory::createPart(Message& msg, User* sender)
{
	return (new PartCmd(msg, this->_owner, sender));
}

ACommand*	CommandFactory::createMode(Message& msg, User* sender)
{
	return (new ModeCmd(msg, this->_owner, sender));
}

ACommand*	CommandFactory::createTopic(Message& msg, User* sender)
{
	return (new TopicCmd(msg, this->_owner, sender));
}

ACommand*	CommandFactory::createList(Message& msg, User* sender)
{
	return (new ListCmd(msg, this->_owner, sender));
}

ACommand*	CommandFactory::createInvite(Message& msg, User* sender)
{
	return (new InviteCmd(msg, this->_owner, sender));
}

ACommand*	CommandFactory::createKick(Message& msg, User* sender)
{
	return (new KickCmd(msg, this->_owner, sender));
}

ACommand*	CommandFactory::createOper(Message& msg, User* sender)
{
	return (new OperCmd(msg, this->_owner, sender));
}

ACommand*	CommandFactory::createKill(Message& msg, User* sender)
{
	return (new KillCmd(msg, this->_owner, sender));
}

ACommand*	CommandFactory::createRehash(Message& msg, User* sender)
{
	return (new RehashCmd(msg, this->_owner, sender));
}

ACommand*	CommandFactory::createPing(Message& msg, User* sender)
{
	return (new PingCmd(msg, this->_owner, sender));
}

ACommand*	CommandFactory::createPong(Message& msg, User* sender)
{
	return (new PongCmd(msg, this->_owner, sender));
}

ACommand*	CommandFactory::createVersion(Message& msg, User* sender)
{
	return (new VersionCmd(msg, this->_owner, sender));
}

ACommand*	CommandFactory::createInfo(Message& msg, User* sender)
{
	return (new InfoCmd(msg, this->_owner, sender));
}

