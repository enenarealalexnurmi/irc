/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 12:21:46 by enena             #+#    #+#             */
/*   Updated: 2022/02/27 14:59:52 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandFactory.hpp"

CommandFactory::CommandFactory(Server& owner) : 
	_owner(owner)
{
	this->dict.insert(values(std::string("NICK"), &createNick));
	this->dict.insert(values(std::string("USER"), &createUser));
	this->dict.insert(values(std::string("PASS"), &createPass));
}

CommandFactory::~CommandFactory()
{
}

ACommand*	CommandFactory::createNick(Message& msg, User* sender)
{
	return new Nick(msg, this->_owner, sender);
}

ACommand*	CommandFactory::createPass(Message& msg, User* sender)
{
	return new Nick(msg, this->_owner, sender);
}

ACommand*	CommandFactory::createUser(Message& msg, User* sender)
{
	return new Nick(msg, this->_owner, sender);
}
