/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 12:21:46 by enena             #+#    #+#             */
/*   Updated: 2022/03/04 04:22:33 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandFactory.hpp"
#include "NickCmd.hpp"
#include "PassCmd.hpp"
#include "UserCmd.hpp"

CommandFactory::CommandFactory(Server* owner) : 
	_owner(owner)
{
	this->dict.insert(valueDict(std::string("NICK"), &CommandFactory::createNick));
	this->dict.insert(valueDict(std::string("USER"), &CommandFactory::createUser));
	this->dict.insert(valueDict(std::string("PASS"), &CommandFactory::createPass));
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
