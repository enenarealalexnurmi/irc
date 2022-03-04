/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PongCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 03:01:49 by enena             #+#    #+#             */
/*   Updated: 2022/03/04 07:50:07 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PongCmd.hpp"

PongCmd::PongCmd(Message& msg, Server* owner, User* sender) :
	ACommand(msg, owner, sender){}

PongCmd::~PongCmd(){}

int	PongCmd::execute()
{
    //if (!this->_base.getParams().empty())
		// throw error
	if (this->_sender)
    {
        if (_base.getParams().size() <= 0 || _base.getParams()[0] != _owner->getServername())
		    return (sendError(*_sender, ERR_NOSUCHSERVER, _base.getParams().size() > 0 ? _base.getParams()[0] : ""));
	    _sender->removeFlag(PINGING);
    }
	return 0;
}