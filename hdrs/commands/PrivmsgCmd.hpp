/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivmsgCmd.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 04:10:20 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:23:04 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVMSGCMD_HPP
#define PRIVMSGCMD_HPP
#include "ACommand.hpp"

class PrivmsgCmd : public ACommand
{
public:
	PrivmsgCmd(Message& msg, Server* owner = NULL, User* sender = NULL);
	~PrivmsgCmd(void);
	void	whyNotAllowed(void) const;
	void	execute(void);
};
#endif