/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 09:24:51 by enena             #+#    #+#             */
/*   Updated: 2022/03/01 02:55:00 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"
#define	MSGLEN 512

Message::Message(const int sockfd)
{
	char		buff[MSGLEN];
	int			bytesRead;
	int			

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
	// if (text.length() == 512)
	// 	text = text.substr(0, 510) + "\r\n";
	// if (bytesRead <= 0)
	// 	return -1;
	// while (text.find("\r\n") != std::string::npos)
	// 	text.replace(text.find("\r\n"), 2, "\n");
	// std::cout << "msg text: " << text << std::endl; //delete
	// return (512 - slen);

Message::Message(const std::string& str) :
	_fullStr(str)
{
	this->_fullSize = this->_fullStr.size();
	this->parse();
}

Message&	Message::operator=(const Message& other)
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

void		Message::parse(void)
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

void		Message::sendIt(const int sockfd) const
{
	if (this->_fullSize > 0)
		send(sockfd, this->_fullStr.c_str(), this->_fullSize, 0);
}
