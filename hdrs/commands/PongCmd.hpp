/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PongCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 03:00:56 by enena             #+#    #+#             */
/*   Updated: 2022/03/04 22:07:08 by enena            ###   ########.fr       */
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
	void execute(void);
};
#endif