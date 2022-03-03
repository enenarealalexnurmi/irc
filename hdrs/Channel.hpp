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

class User;

class Channel {
private:
	std::string 				_name;
	std::vector<User *> 		_operators;
	std::vector<User *> 		_speakers;
	std::string 				_pass;
	unsigned short 				_limit;
	std::vector <std::string> 	_ban_masks;
	unsigned char 				_flags;
	std::vector<User *> 		_users;
	std::string 				_topic;
	std::vector<User *> 		_invited_users;

public:
	Channel(const std::string &name, User &creator, const std::string &pass = "");
	virtual ~Channel();

	const std::string				getName() const;
	const std::string				getTopic() const;
	unsigned char					getFlags() const;

	void							setTopic(User &user, const std::string &topic);
	void							setLimit(unsigned short limit);
	void							setPass(User &user, const std::string &pass);

	bool							isOperator(const User &user) const;
	bool							isSpeaker(const User &user) const;
	bool							isInvite(const User &user) const;
	bool							isInChannel(const std::string &nickname) const;
	bool							isEmpty() const;

	void							addFlag(unsigned char flag);
	void							delFlag(unsigned char flag);

	void							addOperator(const User &user);
	void							delOperator(const User &user);

	void							addSpeaker(const User &user);
	void							delSpeaker(const User &user);

	void							addBanMasks(const std::string &mask);
	void							delBanMasks(const std::string &mask);

	void							addConnect(const User &user, const std::string &key);
	void							delConnect(const User &user);

	void							addInvite(const User &user, const User &receiver);
	void							delInvite(const User &user);

	void							sendMessage(std::string &message, User &from, bool includeUser) const;
	void							printChannelInfo(const User &user);
	void							printCreateInfo(User &user);
	std::string						printFlag() const;
};


#endif
