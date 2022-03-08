/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:28:28 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 08:53:47 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOINCMD_HPP
#define JOINCMD_HPP
#include "ACommand.hpp"

class JoinCmd : public ACommand
{
private:
	std::queue<std::string>	_channels;
	std::queue<std::string>	_keys;

	void	validateChannelName(std::string channelName);
	void	connectToChannel(std::string channelName, std::string key);
public:
	JoinCmd(Message& msg, Server* owner = NULL, User* sender = NULL);
	~JoinCmd(void);
	void	whyNotAllowed(void) const;
	void	execute(void);
};
#endif