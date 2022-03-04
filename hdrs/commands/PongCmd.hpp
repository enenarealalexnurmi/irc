/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PongCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 03:00:56 by enena             #+#    #+#             */
/*   Updated: 2022/03/04 07:02:41 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PONGCMD_HPP
#define PONGCMD_HPP
#include "ACommand.hpp"

class PongCmd : public ACommand
{
public:
	PongCmd(Message& msg, Server* owner = nullptr, User* sender = nullptr);
	~PongCmd(void);
	int	execute(void);
};
#endif