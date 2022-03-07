/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InfoCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:41:55 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:23:13 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFOCMD_HPP
#define INFOCMD_HPP
#include "ACommand.hpp"

class InfoCmd : public ACommand
{
public:
	InfoCmd(Message& msg, Server* owner = NULL, User* sender = NULL);
	~InfoCmd(void);
	void	whyNotAllowed(void) const;
	void	execute(void);
};
#endif