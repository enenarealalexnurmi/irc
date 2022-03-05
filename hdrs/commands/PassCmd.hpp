/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 02:33:53 by enena             #+#    #+#             */
/*   Updated: 2022/03/04 22:07:02 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASSCMD_HPP
#define PASSCMD_HPP
#include "ACommand.hpp"

class PassCmd : public ACommand
{
public:
	PassCmd(Message& msg, Server* owner = nullptr, User* sender = nullptr);
	~PassCmd(void);
	void execute(void);
};
#endif
