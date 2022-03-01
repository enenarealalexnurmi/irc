/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:37:20 by enena             #+#    #+#             */
/*   Updated: 2022/03/01 04:08:26 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ACommand.hpp"

class NickCmd : public ACommand
{
public:
	NickCmd(Message& msg, Server& owner, User* sender = nullptr);
	~NickCmd(void);
	int	execute(void);
};