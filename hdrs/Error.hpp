/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:59:49 by enena             #+#    #+#             */
/*   Updated: 2022/03/06 17:39:43 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP
#define ERROR_HPP
#include <exception>
#include "ACommand.hpp"
#include "Message.hpp"

class Error : public std::exception
{
public:
typedef enum errType
{
	ERR_UNKNOWNCOMMAND,
	ERR_NEEDMOREPARAMS,
	ERR_ALREADYREGISTRED,
	ERR_ERRONEUSNICKNAME,
	ERR_NICKNAMEINUSE,
	ERR_NOORIGIN,
	ERR_NOSUCHSERVER,
	ERR_NORECIPIENT,
	ERR_NOTEXTTOSEND
}	errType;
private:
	Message&	_msg;
	errType		_type;
public:
	Error(errType type, Message& msg) throw();
	~Error() throw();
	Message*	getMessage() const throw();
};

#endif