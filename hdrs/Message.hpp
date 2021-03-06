/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 07:16:30 by enena             #+#    #+#             */
/*   Updated: 2022/03/04 00:04:04 by enena            ###   ########.fr       */
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
	
	void							parse(void);
public:
	Message(const Message& init);
	Message(const std::string& str);
	Message(const int sockfd);
	~Message(void);

	Message&						operator=(const Message& other);
	const std::string&				getPrefix(void) const;
	const std::string&				getCommand(void) const;
	const std::vector<std::string>&	getParams(void) const;
	size_t							getSize(void) const;
	void							sendIt(const int sockfd) const;
};
#endif