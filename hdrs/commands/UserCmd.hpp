/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 02:33:56 by enena             #+#    #+#             */
/*   Updated: 2022/03/04 04:20:23 by enena            ###   ########.fr       */
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
	int	execute(void);
};
#endif
