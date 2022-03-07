/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCmd.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:31:57 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:44:58 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITECMD_HPP
#define INVITECMD_HPP
#include "ACommand.hpp"

class InviteCmd : public ACommand
{
private:
	void	addToInvite(void);
public:
	InviteCmd(Message& msg, Server* owner = NULL, User* sender = NULL);
	~InviteCmd(void);
	void	whyNotAllowed(void) const;
	void	execute(void);
};
#endif