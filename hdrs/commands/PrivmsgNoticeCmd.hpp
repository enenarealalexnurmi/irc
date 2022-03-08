/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivmsgNoticeCmd.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 04:10:20 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 02:24:30 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVMSGNOTICECMD_HPP
#define PRIVMSGNOTICECMD_HPP
#include "ACommand.hpp"
#include <set>

class PrivmsgNoticeCmd : public ACommand
{
public:
	PrivmsgNoticeCmd(Message& msg, Server* owner = NULL, User* sender = NULL);
	~PrivmsgNoticeCmd(void);
	void	whyNotAllowed(void) const;
	void	execute(void);
};
#endif