/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 19:31:21 by enena             #+#    #+#             */
/*   Updated: 2022/02/27 15:04:36 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACOMMAND_HPP
#define ACOMMAND_HPP
#include "Server.hpp"
#include "User.hpp"
#include "Message.hpp"

class Server;
class User;
class Message;

class ACommand
{
private:
	ACommand(const ACommand& init);
	ACommand&	operator=(const ACommand& other);
protected:
	Message						_base;
	Server&						_owner;
	User*						_sender;
	size_t						_countParams;
	ACommand(Message& msg, Server& owner, User* sender = nullptr);
public:
	virtual		~ACommand();	
	virtual int	execute(void) = 0;
};
#endif
