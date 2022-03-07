/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:33:02 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:23:04 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KICKCMD_HPP
#define KICKCMD_HPP
#include "ACommand.hpp"

class KickCmd : public ACommand
{
public:
	KickCmd(Message& msg, Server* owner = NULL, User* sender = NULL);
	~KickCmd(void);
	void	whyNotAllowed(void) const;
	void	execute(void);
};
#endif