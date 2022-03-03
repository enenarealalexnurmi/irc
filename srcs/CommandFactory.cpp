/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 12:21:46 by enena             #+#    #+#             */
/*   Updated: 2022/03/01 02:32:25 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/CommandFactory.hpp"

CommandFactory::CommandFactory(Server& owner) : 
	_owner(owner)
{
	this->dict.insert(valueDict(std::string("NICK"), &createNick));
	this->dict.insert(valueDict(std::string("USER"), &createUser));
	this->dict.insert(valueDict(std::string("PASS"), &createPass));
}

CommandFactory::~CommandFactory()
{
}

ACommand*	CommandFactory::createCommand(Message& msg, User* sender)
{
	if (this->dict.find(msg.getCommand()) != dict.end())
		return (this->*dict.at(msg.getCommand()))(msg, sender);
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
