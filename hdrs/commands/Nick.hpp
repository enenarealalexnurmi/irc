/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:37:20 by enena             #+#    #+#             */
/*   Updated: 2022/02/27 14:26:23 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ACommand.hpp"

class Nick : public ACommand
{
public:
	Nick(Message& msg, Server& owner, User* sender = nullptr);
	~Nick(void);
	int	execute(void);
};