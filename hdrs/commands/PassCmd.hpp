/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 02:33:53 by enena             #+#    #+#             */
/*   Updated: 2022/03/01 04:08:22 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ACommand.hpp"

class PassCmd : public ACommand
{
public:
	PassCmd(Message& msg, Server& owner, User* sender = nullptr);
	~PassCmd(void);
	int	execute(void);
};