/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 09:40:31 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:23:04 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUITCMD_HPP
#define QUITCMD_HPP
#include "ACommand.hpp"

class QuitCmd : public ACommand
{
public:
	QuitCmd(Message& msg, Server* owner = NULL, User* sender = NULL);
	~QuitCmd(void);
	void	whyNotAllowed(void) const;
	void	execute(void);
};
#endif