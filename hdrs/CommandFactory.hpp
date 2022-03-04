/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 12:22:28 by enena             #+#    #+#             */
/*   Updated: 2022/03/03 23:48:11 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDFACTORY_HPP
#define COMMANDFACTORY_HPP

#include <utility>
#include <map>
#include "Server.hpp"
#include "User.hpp"
#include "Message.hpp"
#include "ACommand.hpp"

class ACommand;
class Server;
class User;

class CommandFactory
{
	typedef ACommand* (CommandFactory::*factoryMethod)(Message&, User*);
	typedef std::pair<const std::string&, factoryMethod> valueDict;
private:
	std::map<const std::string&, factoryMethod>	dict;
	Server*		_owner;
	ACommand*	createNick(Message& msg, User* sender);
	ACommand*	createPass(Message& msg, User* sender);
	ACommand*	createUser(Message& msg, User* sender);
public:
	CommandFactory(Server* owner);
	~CommandFactory(void);
	ACommand*	createCommand(Message& msg, User* sender = nullptr);
};
#endif