/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:04:42 by enena             #+#    #+#             */
/*   Updated: 2022/02/27 15:06:48 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ACommand.hpp"

ACommand::ACommand(const ACommand& init) :
	_base(init._base),
	_owner(init._owner),
	_sender(init._sender),
	_countParams(init._countParams)
{}

ACommand::ACommand(Message& msg, Server& owner, User* sender) :
	_base(msg),
	_owner(owner)
{
	
}

ACommand&	ACommand::operator=(const ACommand& other)
{
	if (this == &other)
		return *this;
	return *this;
}