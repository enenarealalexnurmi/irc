/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 09:24:51 by enena             #+#    #+#             */
/*   Updated: 2022/03/04 00:07:32 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"
#define	MSGLEN 512

Message::Message(const int sockfd)
{
	char		buff[MSGLEN];
	int			bytesRead;

	bytesRead = recv(sockfd, buff, 1, 0);
	while ((bytesRead > 0) && (buff[0] != '\n'))
	{
		buff[bytesRead] = 0;
		this->_fullStr += buff;
		buff[0] = 0;
		bytesRead = recv(sockfd, buff, 1, 0);
	}
	buff[0] = 0;
	this->_fullStr += buff;
	this->_fullSize = this->_fullStr.size();
	this->parse();
}

Message::Message(const std::string& str) :
	_fullStr(str)
{
	this->_fullSize = this->_fullStr.size();
	this->parse();
}

Message::~Message(){}

Message&							Message::operator=(const Message& other)
{
	if (this == &other)
		return *this;
	this->_fullStr = other._fullStr;
	this->_fullSize = other._fullSize;
	this->_prefix = other._prefix;
	this->_command = other._command;
	this->_params = other._params;
	return *this;
}

void								Message::parse(void)
{
	std::queue<std::string>	que = split(this->_fullStr, ' ', false);
	if (que.size() > 0 && que.front()[0] == ':')
	{
		this->_prefix = std::string(que.front().begin() + 1, que.front().end());
		que.pop();
	}
	if (que.size() > 0)
	{
		this->_command = que.front();
		que.pop();
	}
	while (que.size() > 0)
	{
		if (que.front()[0] == ':')
		{
			std::string	s(que.front().begin() + 1, que.front().end());
			que.pop();
			while (que.size() > 0)
			{
				s.append(" ");
				s.append(que.front());
				que.pop();
			}
			this->_params.push_back(s);
		}
		else
		{
			this->_params.push_back(que.front());
			que.pop();
		}
	}
}

const std::string&				Message::getPrefix(void) const
{
	return this->_prefix;
}

const std::string&				Message::getCommand(void) const
{
	return this->_command;
}

const std::vector<std::string>&	Message::getParams(void) const
{
	return this->_params;
}

size_t					Message::getSize(void) const
{
	return this->_fullSize;
}

void							Message::sendIt(const int sockfd) const
{
	if (this->_fullSize > 0)
		send(sockfd, this->_fullStr.c_str(), this->_fullSize, 0);
}
