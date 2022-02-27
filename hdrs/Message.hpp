/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 07:16:30 by enena             #+#    #+#             */
/*   Updated: 2022/02/27 15:33:04 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <sys/socket.h>
#include <queue>
#include "utils.hpp"

class Message
{
private:
	std::string						_fullStr;
	size_t							_fullSize;
	std::string						_prefix;
	std::string						_command;
	std::vector<std::string>		_params;
	Message&						operator=(const Message& other);
	void							parse(void);
public:
	Message(const Message& init);
	Message(const std::string& str);
	Message(const int sockfd);
	~Message(void);
	const std::string&				getPrefix(void) const;
	const std::string&				getCommand(void) const;
	const std::vector<std::string>&	getParams(void) const;
	void							sendIt(const int sockfd) const;
};
#endif