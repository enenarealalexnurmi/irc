/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 12:21:46 by enena             #+#    #+#             */
/*   Updated: 2022/03/06 13:57:33 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandFactory.hpp"
#include "NickCmd.hpp"
#include "PassCmd.hpp"
#include "UserCmd.hpp"
#include "PingCmd.hpp"
#include "PongCmd.hpp"
#include "PrivmsgCmd.hpp"

CommandFactory::CommandFactory(Server* owner) : 
	_owner(owner)
{
	this->dict.insert(valueDict(std::string("NICK"), &CommandFactory::createNick));
	this->dict.insert(valueDict(std::string("USER"), &CommandFactory::createUser));
	this->dict.insert(valueDict(std::string("PASS"), &CommandFactory::createPass));
	this->dict.insert(valueDict(std::string("PING"), &CommandFactory::createPing));
	this->dict.insert(valueDict(std::string("PONG"), &CommandFactory::createPong));
	this->dict.insert(valueDict(std::string("PRIVMSG"), &CommandFactory::createPrivmsg));
}

CommandFactory::~CommandFactory()
{
}

ACommand*	CommandFactory::createCommand(Message& msg, User* sender)
{
	if (this->dict.find(msg.getCommand()) != dict.end())
		return (this->*dict.at(msg.getCommand()))(msg, sender);
	else
		return nullptr;
}

ACommand*	CommandFactory::createNick(Message& msg, User* sender)
{
	return new NickCmd(msg, this->_owner, sender);
}

ACommand*	CommandFactory::createPass(Message& msg, User* sender)
{
	return new PassCmd(msg, this->_owner, sender);
}

ACommand*	CommandFactory::createUser(Message& msg, User* sender)
{
	return new UserCmd(msg, this->_owner, sender);
}

ACommand*	CommandFactory::createPing(Message& msg, User* sender)
{
	return new PingCmd(msg, this->_owner, sender);
}

ACommand*	CommandFactory::createPong(Message& msg, User* sender)
{
	return new PongCmd(msg, this->_owner, sender);
}

ACommand*	CommandFactory::createPrivmsg(Message& msg, User* sender)
{
	return new PrivmsgCmd(msg, this->_owner, sender);
}
