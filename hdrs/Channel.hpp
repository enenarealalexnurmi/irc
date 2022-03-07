#ifndef CHANNEL_HPP
#define CHANNEL_HPP


#include "User.hpp"
#include "utils.hpp"
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include "Error.hpp"

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
	std::vector<User *> 	_operators;
	std::vector<User *> 	_speakers;
	std::string 				_pass;
	unsigned short 				_limit;
	std::vector <std::string> 	_ban_masks;
	unsigned char 				_flags;
	std::vector<User *> 	_users;
	std::string 				_topic;
	std::vector<User *> 	_invited_users;

public:
	Channel(const std::string &name, User &creator, const std::string &pass = "");
	virtual ~Channel();

	const std::string				getName() const;
	const std::string				getTopic() const;
	unsigned char					getFlags() const;

	void							setTopic(User &user, const std::string &topic);
	void							setLimit(unsigned short limit);
	void							setPass(User &user, const std::string &pass);

	bool							isOperator(User &user) const;
	bool							isSpeaker(User &user) const;
	bool							isInvite(User &user) const;
	bool							isInChannel(const std::string &nickname) const;
	bool							isEmpty() const;

	void							addFlag(unsigned char flag);
	void							delFlag(unsigned char flag);

	void							addOperator(User &user);
	void							delOperator(User &user);

	void							addSpeaker(User &user);
	void							delSpeaker(User &user);

	void							addBanMasks(const std::string &mask);
	void							delBanMasks(const std::string &mask);
	bool							isBanned(const std::string &mask, const std::string &prefix);

	void							addConnect(User &user, const std::string &key);
	void							delConnect(User &user);

	void							addInvite(User &user, User &receiver);
	void							delInvite(User &user);

	void							sendMessage(const std::string &message, User &from, bool includeUser) const;
	void							printChannelInfo(User &user);
	void							printCreateInfo(User &user);
	std::string						printFlag() const;
	void							displayTopic(User &user);
};


#endif
