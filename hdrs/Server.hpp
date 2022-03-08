#ifndef SERVER_HPP
#define SERVER_HPP

#define RED		"\x1b[31m"
#define GREEN		"\x1b[32m"
#define LIGHT_BLUE	"\x1b[34m"
#define GRAY		"\x1b[90m"
#define YELLOW		"\x1b[33m"
#define PINK		"\x1b[35m"
#define STOP		"\x1b[0m"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <poll.h>
#include <fstream>
#include <map>
#include <fcntl.h>
#include <vector>
#include <stack>
#include "utils.hpp"
#include "Config.hpp"
#include "User.hpp"
#include "ACommand.hpp"
#include "CommandFactory.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Error.hpp"

// class Config;
// class User;
class CommandFactory;
class Channel;

class Server{
    private:
            int                         port;
            int                         socketFd;
            std::string                 password;
            struct sockaddr_in          sockaddr; // выбрали из https://www.opennet.ru/docs/RUS/socket/node4.html
            std::vector<struct pollfd>  userPollFds;
            Config                      config;
            std::vector<std::string>	motd;
            std::vector<std::string>	info;
            std::string                 servername;
            std::string                 version;
            std::string                 debuglvl;
            std::string                 comments;
            std::vector<User *>		connectedUsers;
            CommandFactory*             callCmd;
            id_t                        timeout;
            size_t                      maxChannels;
            std::map<std::string, Channel *> channels;
            Server();

    public:
            Server(int port, const std::string password);
            Server(const Server& other);
            ~Server();

            int createSocket();
            void serverMagic();
            void executeLoop();
            void receiveMessage();
            void deleteUsers();
            void pingMonitor();
            void manageCommand(ACommand* cmd);
            void deleteChannels();
            bool isPrivilegedOperator(std::string nicname, std::string password);

            const std::string                                   getPassword();
            std::vector<std::string>	                        getMotd();
            std::vector<std::string>	                        getInfo();
            const std::string                                   getServername();
            std::vector<User *>&                                getConnectedUsers();
            id_t                                                getTimeout();
            size_t                                              getMaxChannels();
            std::map<std::string, Channel *>&                   getChannels();
            const std::string                                   getVersion();
            const std::string                                   getDebuglvl();
            const std::string                                   getComments();
            bool                                                hasNickname(const std::string &nickname) const;
            bool                                                hasChannel(const std::string &channelname) const;
            void                                                notifyUsersAbout(User &user, const Message &notification);
            void                                                checkRegistration(User &user);
            User*                                               getUserByName(const std::string &name);
            void                                                rereadConfig();
            int                                                 getSockfd();
};

#endif
