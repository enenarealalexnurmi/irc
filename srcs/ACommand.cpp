/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:04:42 by enena             #+#    #+#             */
/*   Updated: 2022/03/04 00:08:49 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/ACommand.hpp"

ACommand::ACommand(const ACommand& init) :
	_base(init._base),
	_owner(init._owner),
	_sender(init._sender),
	_countParams(init._countParams)
{}

ACommand::ACommand(Message& msg, Server* owner, User* sender) :
	_base(msg),
	_owner(owner),
	_sender(sender),
	_countParams(msg.getParams().size())
{}

ACommand::~ACommand(){}

ACommand&	ACommand::operator=(const ACommand& other)
{
	if (this == &other)
		return *this;
	this->_base = other._base;
	this->_owner = other._owner;
	this->_sender = other._sender;
	this->_countParams = other._countParams;
	return *this;
}