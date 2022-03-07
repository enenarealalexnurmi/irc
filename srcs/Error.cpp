/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:59:08 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 01:29:27 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Error.hpp"

Error::Error(errType type, User* sender, std::string arg1, std::string arg2) :
	_type(type),
	_sender(sender),
	_arg1(arg1),
	_arg2(arg2)
{}

Error::~Error(){}

Message* Error::getMessage(void)
{
	std::string	msg = ":" + _sender->getServername() + " " + std::to_string(_type) + " " + _sender->getNickname() + " ";
	switch (this->_type)
	{
	case ERR_NOSUCHNICK:
		msg += this->_arg1 + " :No such nick/channel\n";
		break;
	case ERR_NOSUCHSERVER:
		msg += this->_arg1 + " :No such server\n";
		break;
	case ERR_NOSUCHCHANNEL:
		msg += this->_arg1 + " :No such channel\n";
		break;
	case ERR_CANNOTSENDTOCHAN:
		msg += this->_arg1 + " :Cannot send to channel\n";
		break;
	case ERR_TOOMANYCHANNELS:
		msg += this->_arg1 + " :You have joined too many channels\n";
		break;
	case ERR_WASNOSUCHNICK:
		msg += this->_arg1 + " :There was no such nickname\n";
		break;
	case ERR_TOOMANYTARGETS:
		msg += this->_arg1 + " :Duplicate recipients. No this->_arg1 delivered\n";
		break;
	case ERR_NOORIGIN:
		msg += ":No origin specified\n";
		break;
	case ERR_NORECIPIENT:
		msg += ":No recipient given (" + this->_arg1 + ")\n";
		break;
	case ERR_NOTEXTTOSEND:
		msg += ":No text to send\n";
		break;
	case ERR_NOTOPLEVEL:
		msg += this->_arg1 + " :No toplevel domain specified\n";
		break;
	case ERR_WILDTOPLEVEL:
		msg += this->_arg1 + " :Wildcard in toplevel domain\n";
		break;
	case ERR_UNKNOWNCOMMAND:
		msg += this->_arg1 + " :Unknown command\n";
		break;
	case ERR_NOMOTD:
		msg += ":MOTD File is missing\n";
		break;
	case ERR_NOADMININFO:
		msg += this->_arg1 + " :No administrative info available\n";
		break;
	case ERR_FILEERROR:
		msg += ":File error doing \n" + this->_arg1 + " on " + this->_arg2 + "\n";
		break;
	case ERR_NONICKNAMEGIVEN:
		msg += ":No nickname given\n";
		break;
	case ERR_ERRONEUSNICKNAME:
		msg += this->_arg1 + " :Erroneus nickname\n";
		break;
	case ERR_NICKNAMEINUSE:
		msg += this->_arg1 + " :Nickname is already in use\n";
		break;
	case ERR_NICKCOLLISION:
		msg += this->_arg1 + " :Nickname collision KILL\n";
		break;
	case ERR_USERNOTINCHANNEL:
		msg += this->_arg1 + " " + this->_arg2 + " :They aren't on that channel\n";
		break;
	case ERR_NOTONCHANNEL:
		msg += this->_arg1 + " :You're not on that channel\n";
		break;
	case ERR_USERONCHANNEL:
		msg += this->_arg1 + " " + this->_arg2 + " :is already on channel\n";
		break;
	case ERR_NOLOGIN:
		msg += this->_arg1 + " :User not logged in\n";
		break;
	case ERR_SUMMONDISABLED:
		msg += ":SUMMON has been disabled\n";
		break;
	case ERR_USERSDISABLED:
		msg += ":USERS has been disabled\n";
		break;
	case ERR_NOTREGISTERED:
		msg += ":You have not registered\n";
		break;
	case ERR_NEEDMOREPARAMS:
		msg += this->_arg1 + " :Not enough parameters\n";
		break;
	case ERR_ALREADYREGISTRED:
		msg += ":You may not reregister\n";
		break;
	case ERR_NOPERMFORHOST:
		msg += ":Your host isn't among the privileged\n";
		break;
	case ERR_PASSWDMISMATCH:
		msg += ":Password incorrect\n";
		break;
	case ERR_YOUREBANNEDCREEP:
		msg += ":You are banned from this server\n";
		break;
	case ERR_KEYSET:
		msg += this->_arg1 + " :Channel key already set\n";
		break;
	case ERR_CHANNELISFULL:
		msg += this->_arg1 + " :Cannot join channel (+l)\n";
		break;
	case ERR_UNKNOWNMODE:
		msg += this->_arg1 + " :is unknown mode char to me\n";
		break;
	case ERR_INVITEONLYCHAN:
		msg += this->_arg1 + " :Cannot join channel (+i)\n";
		break;
	case ERR_BANNEDFROMCHAN:
		msg += this->_arg1 + " :Cannot join channel (+b)\n";
		break;
	case ERR_BADCHANNELKEY:
		msg += this->_arg1 + " :Cannot join channel (+k)\n";
		break;
	case ERR_NOPRIVILEGES:
		msg += ":Permission Denied- You're not an IRC operator\n";
		break;
	case ERR_CHANOPRIVSNEEDED:
		msg += this->_arg1 + " :You're not channel operator\n";
		break;
	case ERR_CANTKILLSERVER:
		msg += ":You cant kill a server!\n";
		break;
	case ERR_UMODEUNKNOWNFLAG:
		msg += ":Unknown MODE flag\n";
		break;
	case ERR_USERSDONTMATCH:
		msg += ":Cant change mode for other users\n";
		break;
	default:
		msg = "UNKNOWN ERROR\n";
	}
	return new Message(msg);
}
