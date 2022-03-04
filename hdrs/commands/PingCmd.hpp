/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 03:01:15 by enena             #+#    #+#             */
/*   Updated: 2022/03/04 07:02:23 by enena            ###   ########.fr       */
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
	int	execute(void);
};
#endif