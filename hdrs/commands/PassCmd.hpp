/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 02:33:53 by enena             #+#    #+#             */
/*   Updated: 2022/03/04 04:20:09 by enena            ###   ########.fr       */
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
	int	execute(void);
};
#endif
