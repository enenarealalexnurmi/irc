/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:04:42 by enena             #+#    #+#             */
/*   Updated: 2022/02/21 16:54:35 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ACommand.hpp"

ACommand::ACommand(void){};

ACommand::ACommand(const ACommand& init)
{
	operator=(init);
}

ACommand::operator=(const ACommand& other)
{
	if (this == &other)
		return *this;
	return *this;
}