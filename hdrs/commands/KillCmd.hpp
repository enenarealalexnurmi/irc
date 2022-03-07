/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KillCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:42:27 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:23:04 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KILLCMD_HPP
#define KILLCMD_HPP
#include "ACommand.hpp"

class KillCmd : public ACommand
{
public:
	KillCmd(Message& msg, Server* owner = NULL, User* sender = NULL);
	~KillCmd(void);
	void	whyNotAllowed(void) const;
	void	execute(void);
};
#endif