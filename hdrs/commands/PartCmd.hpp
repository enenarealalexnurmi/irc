/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:43:54 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:23:04 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTCMD_HPP
#define PARTCMD_HPP
#include "ACommand.hpp"

class PartCmd : public ACommand
{
public:
	PartCmd(Message& msg, Server* owner = NULL, User* sender = NULL);
	~PartCmd(void);
	void	whyNotAllowed(void) const;
	void	execute(void);
};
#endif