/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RestartCmd.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:43:41 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:23:04 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESTARTCMD_HPP
#define RESTARTCMD_HPP
#include "ACommand.hpp"

class RestartCmd : public ACommand
{
public:
	RestartCmd(Message& msg, Server* owner = NULL, User* sender = NULL);
	~RestartCmd(void);
	void	whyNotAllowed(void) const;
	void	execute(void);
};
#endif