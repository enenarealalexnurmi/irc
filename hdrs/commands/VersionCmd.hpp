/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VersionCmd.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:43:47 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:23:04 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERSIONCMD_HPP
#define VERSIONCMD_HPP
#include "ACommand.hpp"

class VersionCmd : public ACommand
{
public:
	VersionCmd(Message& msg, Server* owner = NULL, User* sender = NULL);
	~VersionCmd(void);
	void	whyNotAllowed(void) const;
	void	execute(void);
};
#endif