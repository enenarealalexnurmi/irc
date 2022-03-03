#include "../hdrs/utils.hpp"
#include <iostream>
#include <string.h>

void loadfile(std::vector<std::string> *arr, std::string const &path)
{
	std::ifstream src(path);
	std::string		line;

	if (src.is_open())
	{
		while (std::getline(src, line))
			arr->push_back(line);
		src.close();
	}
	else
	{
		std::cout << RED << "ERROR: " << STOP << "can't open file(" << path << ").\n";
		exit(1); 
	}
}

int		sendError(User &user, int num, const std::string &arg1,
					 const std::string &arg2)
{
	std::string ernum = std::to_string(num);
	std::string	msg = ":" + user.getServername() + " " + ernum + " " +
							user.getNickname() + " "; //  ":SERVER_NAME ";
    switch (num)
    {
	case ERR_NOSUCHNICK:
		msg += arg1 + " :No such nick/channel\n";
        break;
	case ERR_NOSUCHSERVER:
		msg += arg1 + " :No such server\n";
        break;
	case ERR_NOSUCHCHANNEL:
		msg += arg1 + " :No such channel\n";
        break;
	case ERR_CANNOTSENDTOCHAN:
		msg += arg1 + " :Cannot send to channel\n";
        break;
	case ERR_TOOMANYCHANNELS:
		msg += arg1 + " :You have joined too many channels\n";
        break;
	case ERR_WASNOSUCHNICK:
		msg += arg1 + " :There was no such nickname\n";
        break;
	case ERR_TOOMANYTARGETS:
		msg += arg1 + " :Duplicate recipients. No arg1 delivered\n";
        break;
	case ERR_NOORIGIN:
		msg += ":No origin specified\n";
        break;
	case ERR_NORECIPIENT:
		msg += ":No recipient given (" + arg1 + ")\n";
        break;
	case ERR_NOTEXTTOSEND:
		msg += ":No text to send\n";
        break;
	case ERR_NOTOPLEVEL:
		msg += arg1 + " :No toplevel domain specified\n";
        break;
	case ERR_WILDTOPLEVEL:
		msg += arg1 + " :Wildcard in toplevel domain\n";
        break;
	case ERR_UNKNOWNCOMMAND:
		msg += arg1 + " :Unknown command\n";
        break;
	case ERR_NOMOTD:
		msg += ":MOTD File is missing\n";
        break;
	case ERR_NOADMININFO:
		msg += arg1 + " :No administrative info available\n";
        break;
	case ERR_FILEERROR:
		msg += ":File error doing \n" + arg1 + " on " + arg2 + "\n";
        break;
	case ERR_NONICKNAMEGIVEN:
		msg += ":No nickname given\n";
        break;
	case ERR_ERRONEUSNICKNAME:
		msg += arg1 + " :Erroneus nickname\n";
        break;
	case ERR_NICKNAMEINUSE:
		msg += arg1 + " :Nickname is already in use\n";
        break;
	case ERR_NICKCOLLISION:
		msg += arg1 + " :Nickname collision KILL\n";
        break;
	case ERR_USERNOTINCHANNEL:
		msg += arg1 + " " + arg2 + " :They aren't on that channel\n";
        break;
	case ERR_NOTONCHANNEL:
		msg += arg1 + " :You're not on that channel\n";
        break;
	case ERR_USERONCHANNEL:
		msg += arg1 + " " + arg2 + " :is already on channel\n";
        break;
	case ERR_NOLOGIN:
		msg += arg1 + " :User not logged in\n";
        break;
	case ERR_SUMMONDISABLED:
		msg += ":SUMMON has been disabled\n";
        break;
	case ERR_USERSDISABLED:
		msg += ":USERS has been disabled\n";
        break;
	case ERR_NOTREGISTERED:
		msg += ":You have not registered\n";
        break;
	case ERR_NEEDMOREPARAMS:
		msg += arg1 + " :Not enough parameters\n";
        break;
	case ERR_ALREADYREGISTRED:
		msg += ":You may not reregister\n";
        break;
	case ERR_NOPERMFORHOST:
		msg += ":Your host isn't among the privileged\n";
        break;
	case ERR_PASSWDMISMATCH:
		msg += ":Password incorrect\n";
        break;
	case ERR_YOUREBANNEDCREEP:
		msg += ":You are banned from this server\n";
        break;
	case ERR_KEYSET:
		msg += arg1 + " :Channel key already set\n";
        break;
	case ERR_CHANNELISFULL:
		msg += arg1 + " :Cannot join channel (+l)\n";
        break;
	case ERR_UNKNOWNMODE:
		msg += arg1 + " :is unknown mode char to me\n";
        break;
	case ERR_INVITEONLYCHAN:
		msg += arg1 + " :Cannot join channel (+i)\n";
        break;
	case ERR_BANNEDFROMCHAN:
		msg += arg1 + " :Cannot join channel (+b)\n";
        break;
	case ERR_BADCHANNELKEY:
		msg += arg1 + " :Cannot join channel (+k)\n";
        break;
	case ERR_NOPRIVILEGES:
		msg += ":Permission Denied- You're not an IRC operator\n";
        break;
	case ERR_CHANOPRIVSNEEDED:
		msg += arg1 + " :You're not channel operator\n";
        break;
	case ERR_CANTKILLSERVER:
		msg += ":You cant kill a server!\n";
        break;
	case ERR_NOOPERHOST:
		msg += ":No O-lines for your host\n";
        break;
	case ERR_UMODEUNKNOWNFLAG:
		msg += ":Unknown MODE flag\n";
        break;
	case ERR_USERSDONTMATCH:
		msg += ":Cant change mode for other users\n";
        break;
	default:
		msg += "UNKNOWN ERROR\n";
    }
	send(user.getSockfd(), msg.c_str(), msg.size(), 0);
	return (-1);
}

int		sendReply(User &user, int rpl, const std::string &arg1, const
			std::string &arg2, const std::string &arg3, const std::string &arg4)
{
	std::string ernum = std::to_string(rpl);
	std::string	format = ":" + user.getServername() + " " + ernum + " " + user
			.getNickname() + " ";

	switch(rpl)
    {
    case RPL_USERHOST:
		format += ":" + arg1 + "\n";
        break;
	case RPL_ISON:
		format += ":" + arg1 + "\n";
        break;
	case RPL_AWAY:
		format += arg1 + " :" + arg2 + "\n";
        break;
	case RPL_UNAWAY:
		format += ":You are no longer marked as being away\n";
        break;
	case RPL_NOWAWAY:
		format += ":You have been marked as being away\n";
        break;
	case RPL_WHOISUSER:
		format += arg1 + " " + arg2 + " " + arg3 + " * :" + arg4 + "\n";
        break;
	case RPL_WHOISSERVER:
		format += arg1 + " " + arg2 + " :" + arg3 + "\n";
        break;
	case RPL_WHOISOPERATOR:
		format += arg1 + " :is an IRC operator\n";
        break;
	case RPL_WHOISIDLE:
		format += arg1 + " " + arg2 + " " + arg3 + " :seconds idle\n";
        break;
	case RPL_ENDOFWHOIS:
		format += arg1 + " :End of /WHOIS list\n";
        break;
	case RPL_WHOISCHANNELS:
		format += arg1 + " :" + arg2 + "\n";
        break;
	case RPL_WHOWASUSER:
		format += arg1 + " " + arg2 + " " + arg3 + " * :" + arg4 + "\n";
        break;
	case RPL_ENDOFWHOWAS:
		format += arg1 + " :End of WHOWAS\n";
        break;
	case RPL_LISTSTART:
		format += "Channel :Users  Name\n";
        break;
	case RPL_LIST:
		format += arg1 + " " + arg2 + " :" + arg3 + "\n";
        break;
	case RPL_LISTEND:
		format += ":End of /LIST\n";
        break;
	case RPL_CHANNELMODEIS:
		format += arg1 + " +" + arg2 + "\n";
        break;
	case RPL_NOTOPIC:
		format += arg1 + " :No topic is set\n";
        break;
	case RPL_TOPIC:
		format += arg1 + " :" + arg2 + "\n";
        break;
	case RPL_INVITING:
		format += arg1 + " " + arg2 + "\n";
        break;
	case RPL_SUMMONING:
		format += arg1 + " :Summoning user to IRC\n";
        break;
	case RPL_VERSION:
		format += arg1 + "." + arg2 + " " + arg3 + " :" + arg4 + "\n";
        break;
	case RPL_WHOREPLY:
		format += arg1 + "\n";
        break;
	case RPL_ENDOFWHO:
		format += arg1 + " :End of /WHO list\n";
        break;
	case RPL_NAMREPLY:
		format += arg1 + " :" + arg2 + "\n";
        break;
	case RPL_ENDOFNAMES:
		format += arg1 + " :End of /NAMES list\n";
        break;
	case RPL_LINKS:
		format += arg1 + " " + arg2 + ": " + arg3 + " " + arg4 + "\n";
        break;
	case RPL_ENDOFLINKS:
		format += arg1 + " :End of /LINKS list\n";
        break;
	case RPL_BANLIST:
		format += arg1 + " " + arg2 + "\n";
        break;
	case RPL_ENDOFBANLIST:
		format += arg1 + " :End of channel ban list\n";
        break;
	case RPL_INFO:
		format += ":" + arg1 + "\n";
        break;
	case RPL_ENDOFINFO:
		format += ":End of /INFO list\n";
        break;
	case RPL_MOTDSTART:
		format += ":- " + arg1 + " Message of the day - \n";
        break;
	case RPL_MOTD:
		format += ":- " + arg1 + "\n";
        break;
	case RPL_ENDOFMOTD:
		format += ":End of /MOTD command\n";
        break;
	case RPL_YOUREOPER:
		format += ":You are now an IRC operator\n";
        break;
	case RPL_REHASHING:
		format += arg1 + " :Rehashing\n";
        break;
	case RPL_TIME:
		format += arg1 + " :" + arg2;
        break;
	case RPL_USERSSTART:
		format += ":UserID   Terminal  Host\n";
        break;
	case RPL_USERS:
		format += ":%-8s %-9s %-8s\n";
        break;
	case RPL_ENDOFUSERS:
		format += ":End of users\n";
        break;
	case RPL_NOUSERS:
		format += ":Nobody logged in\n";
        break;
	case RPL_TRACELINK:
		format += "Link " + arg1 + " " + arg2 + " " + arg3 + "\n";
        break;
	case RPL_TRACECONNECTING:
		format += "Try. " + arg1 + " " + arg2 + "\n";
        break;
	case RPL_TRACEHANDSHAKE:
		format += "H.S. " + arg1 + " " + arg2 + "\n";
        break;
	case RPL_TRACEUNKNOWN:
		format += "???? " + arg1 + " " + arg2 + "\n";
        break;
	case RPL_TRACEOPERATOR:
		format += "Oper " + arg1 + " " + arg2 + "\n";
        break;
	case RPL_TRACEUSER:
		format += "User " + arg1 + " " + arg2 + "\n";
        break;
	case RPL_TRACENEWTYPE:
		format += arg1 + " 0 " + arg2 + "\n";
        break;
	case RPL_TRACELOG:
		format += "File " + arg1 + " " + arg2 + "\n";
        break;
	case RPL_STATSCOMMANDS:
		format += arg1 + " " + arg2 + "\n";
        break;
	case RPL_STATSCLINE:
		format += "C " + arg1 + " * " + arg2 + " " + arg3 + " " + arg4 + "\n";
        break;
	case RPL_STATSNLINE:
		format += "N " + arg1 + " * " + arg2 + " " + arg3 + " " + arg4 + "\n";
        break;
	case RPL_STATSILINE:
		format += "I " + arg1 + " * " + arg2 + " " + arg3 + " " + arg4 + "\n";
        break;
	case RPL_STATSKLINE:
		format += "K " + arg1 + " * " + arg2 + " " + arg3 + " " + arg4 + "\n";
        break;
	case RPL_STATSYLINE:
		format += "Y " + arg1 + " * " + arg2 + " " + arg3 + " " + arg4 + "\n";
        break;
	case RPL_ENDOFSTATS:
		format += arg1 + " :End of /STATS report\n";
        break;
	case RPL_STATSLLINE:
		format += "L " + arg1 + " * " + arg2 + " " + arg3 + "\n";
        break;
	case RPL_STATSUPTIME:
		format += ":Server Up %d days %d:%02d:%02d\n";
        break;
	case RPL_STATSOLINE:
		format += "O " + arg1 + " * " + arg2 + "\n";
        break;
	case RPL_STATSHLINE:
		format += "H " + arg1 + " * " + arg2 + "\n";
        break;
	case RPL_UMODEIS:
		format += arg1 + "\n";
        break;
	case RPL_LUSERCLIENT:
		format += ":There are " + arg1 + " users and " + arg2 + " invisible on "
				  + arg3 + " servers\n";
        break;
	case RPL_LUSEROP:
		format += arg1 + " :operator(s) online\n";
        break;
	case RPL_LUSERUNKNOWN:
		format += arg1 + " :unknown connection(s)\n";
        break;
	case RPL_LUSERCHANNELS:
		format += arg1 + " :channels formed\n";
        break;
	case RPL_LUSERME:
		format += ":I have " + arg1 + " clients and " + arg2 + " servers\n";
        break;
	case RPL_ADMINME:
		format += arg1 + " :Administrative info\n";
        break;
	case RPL_ADMINLOC1:
		format += ":Name     " + arg1 + "\n";
        break;
	case RPL_ADMINLOC2:
		format += ":Nickname " + arg1 + "\n";
        break;
	case RPL_ADMINEMAIL:
		format += ":E-Mail   " + arg1 + "\n";
        break;
	default:
		format += "UNKNOWN REPLY\n";
    }
	send(user.getSockfd(), format.c_str(), format.size(), 0);
	return 0;
}

std::queue<std::string>	split(const std::string &s, char sep, bool include)
{
	std::queue<std::string>	ret;
	std::string::const_iterator	i = s.begin();
	while(i != s.end())
	{
		while (i != s.end() && *i == sep)
			++i;
		std::string::const_iterator	j = std::find(i, s.end(), sep);
		if (i != s.end())
		{
			if (include && j != s.end())
				ret.push(std::string(i, j + 1));
			else
				ret.push(std::string(i, j));
			i = j;
		}
	}
	return ret;
}