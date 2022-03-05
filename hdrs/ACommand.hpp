/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 19:31:21 by enena             #+#    #+#             */
/*   Updated: 2022/03/04 21:53:12 by enena            ###   ########.fr       */
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
	ACommand(Message& msg, Server* owner = nullptr, User* sender = nullptr);
	void			checkCountParam(void);

	// bool		userIsReg(void) const;
public:
	virtual			~ACommand();	
	virtual void	execute(void) = 0;
	User*			getSender(void) const;
};
#endif
