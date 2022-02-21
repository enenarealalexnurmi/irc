/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 19:31:21 by enena             #+#    #+#             */
/*   Updated: 2022/02/21 16:29:15 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"

class Server;
class User;
class Message;

class ACommand
{
private:
	ACommand(void);
	ACommand(const ACommand& init);
	ACommand&	operator=(const ACommand& other);
protected:
	std::string					_name;
	std::vector<std::string>	_params;
	Server&						_owner;
	User*						_sender;
	unsigned int				_countParams;
	ACommand(Message& msg, Server& owner);
public:
	virtual		~ACommand();
	virtual int	execute(void) = 0;
};
