/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:29:06 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:23:04 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERCMD_HPP
#define OPERCMD_HPP
#include "ACommand.hpp"

class OperCmd : public ACommand
{
public:
	OperCmd(Message& msg, Server* owner = NULL, User* sender = NULL);
	~OperCmd(void);
	void	whyNotAllowed(void) const;
	void	execute(void);
};
#endif