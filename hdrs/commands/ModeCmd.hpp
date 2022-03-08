/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 14:43:59 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 03:42:17 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODECMD_HPP
#define MODECMD_HPP
#include "ACommand.hpp"

class ModeCmd : public ACommand
{
private:
	void	setFlagModeChannel(const Message &msg, User* user);
	void	setFlagModeUser(const std::string& flag, User* user);
public:
	ModeCmd(Message& msg, Server* owner = NULL, User* sender = NULL);
	~ModeCmd(void);
	void	whyNotAllowed(void) const;
	void	execute(void);
};
#endif