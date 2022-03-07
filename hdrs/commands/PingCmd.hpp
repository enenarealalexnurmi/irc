/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 03:01:15 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:23:04 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PINGCMD_HPP
#define PINGCMD_HPP
#include "ACommand.hpp"

class PingCmd : public ACommand
{
public:
	PingCmd(Message& msg, Server* owner = NULL, User* sender = NULL);
	~PingCmd(void);
	void	whyNotAllowed(void) const;
	void	execute(void);
};
#endif