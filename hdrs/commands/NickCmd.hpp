/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:37:20 by enena             #+#    #+#             */
/*   Updated: 2022/03/05 00:08:21 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NICKCMD_HPP
#define NICKCMD_HPP
#include "ACommand.hpp"
#include <cctype>

class NickCmd : public ACommand
{
private:
	void	validateNickname(const std::string& nick);
public:
	NickCmd(Message& msg, Server* owner = nullptr, User* sender = nullptr);
	~NickCmd(void);
	void	execute(void);
};
#endif
