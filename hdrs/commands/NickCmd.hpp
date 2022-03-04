/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:37:20 by enena             #+#    #+#             */
/*   Updated: 2022/03/03 23:38:06 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NICKCMD_HPP
#define NICKCMD_HPP
#include "ACommand.hpp"

class NickCmd : public ACommand
{
public:
	NickCmd(Message& msg, Server* owner = nullptr, User* sender = nullptr);
	~NickCmd(void);
	int	execute(void);
};
#endif
