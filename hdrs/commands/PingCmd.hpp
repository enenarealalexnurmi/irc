/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 03:01:15 by enena             #+#    #+#             */
/*   Updated: 2022/03/04 22:07:05 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PINGCMD_HPP
#define PINGCMD_HPP
#include "ACommand.hpp"

class PingCmd : public ACommand
{
public:
	PingCmd(Message& msg, Server* owner = nullptr, User* sender = nullptr);
	~PingCmd(void);
	void execute(void);
};
#endif