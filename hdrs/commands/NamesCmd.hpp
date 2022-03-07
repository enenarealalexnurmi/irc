/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NamesCmd.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:43:57 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:23:04 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NAMESCMD_HPP
#define NAMESCMD_HPP
#include "ACommand.hpp"

class NamesCmd : public ACommand
{
public:
	NamesCmd(Message& msg, Server* owner = NULL, User* sender = NULL);
	~NamesCmd(void);
	void	whyNotAllowed(void) const;
	void	execute(void);
};
#endif