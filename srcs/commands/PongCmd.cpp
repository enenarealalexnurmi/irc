/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PongCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 03:01:49 by enena             #+#    #+#             */
/*   Updated: 2022/03/04 23:13:14 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PongCmd.hpp"

PongCmd::PongCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender){}

PongCmd::~PongCmd(void){}

void	PongCmd::execute(void)
{
    //if (!this->_base.getParams().empty())
		// throw error
	if (this->_sender)
    {
        if (_base.getParams().size() <= 0 || _base.getParams()[0] != _owner->getServername())
		    return (sendError(*_sender, ERR_NOSUCHSERVER, _base.getParams().size() > 0 ? _base.getParams()[0] : ""));
	    _sender->removeFlag(PINGING);
    }
}