/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:37:20 by enena             #+#    #+#             */
/*   Updated: 2022/03/08 00:37:27 by enena            ###   ########.fr       */
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
	NickCmd(Message& msg, Server* owner = NULL, User* sender = NULL);
	~NickCmd(void);
	void	whyNotAllowed(void) const;
	void	execute(void);
};
#endif