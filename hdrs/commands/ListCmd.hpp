/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 14:44:01 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:23:04 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTCMD_HPP
#define LISTCMD_HPP
#include "ACommand.hpp"

class ListCmd : public ACommand
{
public:
	ListCmd(Message& msg, Server* owner = NULL, User* sender = NULL);
	~ListCmd(void);
	void	whyNotAllowed(void) const;
	void	execute(void);
};
#endif