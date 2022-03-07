/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 02:33:56 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 00:37:15 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERCMD_HPP
#define USERCMD_HPP
#include "ACommand.hpp"

class UserCmd : public ACommand
{
public:
	UserCmd(Message& msg, Server* owner = NULL, User* sender = NULL);
	~UserCmd(void);
	void	whyNotAllowed(void) const;
	void	execute(void);
};
#endif