/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 12:22:28 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 04:36:53 by enena            ###   ########.fr       */
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
	typedef std::pair<const std::string, factoryMethod> valueDict;
private:
	std::map<const std::string, factoryMethod>	dict;
	Server*		_owner;
	ACommand*	createQuit(Message& msg, User* sender);
	ACommand*	createPass(Message& msg, User* sender);
	ACommand*	createNick(Message& msg, User* sender);
	ACommand*	createUser(Message& msg, User* sender);
	ACommand*	createPrivmsgNotice(Message& msg, User* sender);
	ACommand*	createJoin(Message& msg, User* sender);
	ACommand*	createPart(Message& msg, User* sender);
	ACommand*	createMode(Message& msg, User* sender);
	ACommand*	createTopic(Message& msg, User* sender);
	ACommand*	createNames(Message& msg, User* sender);
	ACommand*	createList(Message& msg, User* sender);
	ACommand*	createInvite(Message& msg, User* sender);
	ACommand*	createKick(Message& msg, User* sender);
	ACommand*	createOper(Message& msg, User* sender);
	ACommand*	createKill(Message& msg, User* sender);
	ACommand*	createRehash(Message& msg, User* sender);
	ACommand*	createRestart(Message& msg, User* sender);
	ACommand*	createPing(Message& msg, User* sender);
	ACommand*	createPong(Message& msg, User* sender);
	ACommand*	createVersion(Message& msg, User* sender);
	ACommand*	createInfo(Message& msg, User* sender);
public:
	CommandFactory(Server* owner);
	~CommandFactory(void);
	ACommand*	createCommand(Message& msg, User* sender = NULL);
};
#endif