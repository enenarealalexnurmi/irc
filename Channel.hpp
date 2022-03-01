#ifndef CHANNEL_HPP
#define CHANNEL_HPP


#include "User.hpp"
#include "utils.hpp"
#include <string>
#include <vector>
#include <map>
#include <ctime>

#define NOMESSAGE	0b000000
#define PRIVATE		0b000001
#define SECRET		0b000010
#define MODERATED	0b000100
#define INVITEONLY	0b001000
#define TOPICSET	0b010000

class Channel {
private:
	std::string 				_name;
	std::vector<const User *> 	_operators;
	std::vector<const User *> 	_speakers;
	std::string 				_pass;
	unsigned short 				_limit;
	std::vector <std::string> 	_ban_masks;
	unsigned char 				_flags;
	std::vector<const User *> 	_users;
	std::string 				_topic;
	std::vector<const User *> 	_invited_users;

public:
	Channel(const std::string &name, const User &creator, const std::string &pass = "");
	virtual ~Channel();

	const std::string				getName() const;
	const std::string				getTopic() const;
	unsigned char					getFlags() const;

	void							setTopic(User &user, const std::string &topic);
	void							setLimit(unsigned short limit);
	void							setPass(User &user, const std::string &pass);

	bool							isOperator(const User &user) const;
	bool							isSpeaker(const User &user) const;
	void							sendMessage(const std::string &message, const User &from, bool includeUser) const;
	void							sendInfo(User &user);
};


#endif
