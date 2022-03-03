/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 02:33:56 by enena             #+#    #+#             */
/*   Updated: 2022/03/01 04:06:16 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ACommand.hpp"

class UserCmd : public ACommand
{
public:
	UserCmd(Message& msg, Server& owner, User* sender = nullptr);
	~UserCmd(void);
	int	execute(void);
};