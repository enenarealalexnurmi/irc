/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 19:31:21 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 02:49:48 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACOMMAND_HPP
#define ACOMMAND_HPP
#include "Server.hpp"
#include "User.hpp"
#include "Message.hpp"
#include "Error.hpp"

class Server;
class User;
class Message;

class ACommand
{
private:
	ACommand(const ACommand& init);
	ACommand&	operator=(const ACommand& other);
protected:
	Message&		_base;
	Server*			_owner;
	User*			_sender;
	size_t			_countParams;
	size_t			_reqCountParam;
	bool			_allowed;
	ACommand(Message& msg, Server* owner = NULL, User* sender = NULL);
	void			checkCountParam(void);
public:
	virtual			~ACommand();	
	virtual void	execute(void) = 0;
	virtual void	whyNotAllowed(void) const = 0;
	bool			isAllowed(void) const;
	User*			getSender(void) const;
};
#endif
