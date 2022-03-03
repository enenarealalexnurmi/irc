/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 12:22:28 by enena             #+#    #+#             */
/*   Updated: 2022/03/01 03:58:13 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDFACTORY_HPP
#define COMMANDFACTORY_HPP

#include <utility>
#include <map>
#include "Server.hpp"
#include "User.hpp"
#include "Message.hpp"
#include "commands/NickCmd.hpp"
#include "commands/PassCmd.hpp"
#include "commands/UserCmd.hpp"

class Server;
class Message;
class User;

class CommandFactory
{
	typedef ACommand* (CommandFactory::*factoryMethod)(Message&, User*);
	typedef std::pair<const std::string&, factoryMethod> valueDict;
private:
	std::map<const std::string&, factoryMethod>	dict;
	Server&		_owner;
	ACommand*	createNick(Message& msg, User* sender);
	ACommand*	createPass(Message& msg, User* sender);
	ACommand*	createUser(Message& msg, User* sender);
public:
	CommandFactory(Server& owner);
	~CommandFactory(void);
	ACommand*	createCommand(Message& msg, User* sender = nullptr);
};
#endif