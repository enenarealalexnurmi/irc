/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RehashCmd.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:43:38 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:23:04 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REHASHCMD_HPP
#define REHASHCMD_HPP
#include "ACommand.hpp"

class RehashCmd : public ACommand
{
public:
	RehashCmd(Message& msg, Server* owner = NULL, User* sender = NULL);
	~RehashCmd(void);
	void	whyNotAllowed(void) const;
	void	execute(void);
};
#endif