/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivmsgCmd.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 04:10:20 by enena             #+#    #+#             */
/*   Updated: 2022/03/04 07:11:09 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVMSGCMD_HPP
#define PRIVMSGCMD_HPP
#include "ACommand.hpp"

class PrivmsgCmd : public ACommand
{
public:
	PrivmsgCmd(Message& msg, Server* owner = nullptr, User* sender = nullptr);
	~PrivmsgCmd(void);
	int	execute(void);
};
#endif