/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:59:49 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 03:36:11 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP
#define ERROR_HPP
#include <exception>
#include "ACommand.hpp"
#include "Message.hpp"
#include "User.hpp"

class User;
class Message;

class Error : public std::exception
{
public:
typedef enum errType
{
	ERR_NOTREGISTERED,
	ERR_UNKNOWNCOMMAND,
	ERR_NEEDMOREPARAMS,
	ERR_ALREADYREGISTRED,
	ERR_ERRONEUSNICKNAME,
	ERR_NICKNAMEINUSE,
	ERR_NOORIGIN,
	ERR_NOSUCHSERVER,
	ERR_NOSUCHNICK,
	ERR_NORECIPIENT,
	ERR_NOTEXTTOSEND,
	ERR_NOSUCHCHANNEL,
	ERR_TOOMANYCHANNELS,
	ERR_NOTONCHANNEL,
	ERR_PASSWDMISMATCH,
	ERR_USERNOTINCHANNEL,
	ERR_CHANOPRIVSNEEDED,
	ERR_NOPRIVILEGES,
	ERR_USERSDONTMATCH,
	ERR_UMODEUNKNOWNFLAG,
	ERR_USERONCHANNEL,
	ERR_CANTKILLSERVER,
	ERR_KEYSET,
	ERR_BADCHANNELKEY,
	ERR_CHANNELISFULL,
	ERR_INVITEONLYCHAN,
	ERR_BANNEDFROMCHAN,
	ERR_TOOMANYTARGETS,
	ERR_CANNOTSENDTOCHAN,
	ERR_UNKNOWNMODE
}	errType;
private:
	errType				_type;
	User*				_sender;
	const std::string&	_arg1;
	const std::string&	_arg2;
public:
	Error(errType type, User* sender, const std::string& arg1 = "", const std::string& arg2 = "") throw();
	~Error() throw();
	Message*	getMessage() const throw();
};

#endif