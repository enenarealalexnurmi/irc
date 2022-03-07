/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopicCmd.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:43:44 by enena             #+#    #+#             */
/*   Updated: 2022/03/07 21:23:04 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPICCMD_HPP
#define TOPICCMD_HPP
#include "ACommand.hpp"

class TopicCmd : public ACommand
{
public:
	TopicCmd(Message& msg, Server* owner = NULL, User* sender = NULL);
	~TopicCmd(void);
	void	whyNotAllowed(void) const;
	void	execute(void);
};
#endif