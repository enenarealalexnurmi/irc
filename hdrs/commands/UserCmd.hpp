/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 02:33:56 by enena             #+#    #+#             */
/*   Updated: 2022/03/04 22:07:21 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERCMD_HPP
#define USERCMD_HPP
#include "ACommand.hpp"

class UserCmd : public ACommand
{
public:
	UserCmd(Message& msg, Server* owner = nullptr, User* sender = nullptr);
	~UserCmd(void);
	void execute(void);
};
#endif
