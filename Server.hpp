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
#include "utils.hpp"
#include "Operator.hpp"
#include "Config.hpp"
#include "User.hpp"
//#include "History.hpp"
//#include "sendError.hpp"
//#include "Channel.hpp"
//#include "sendReply.hpp"

class Operator;
class Config;
class User;
//class Channel;
//class UserInfo;
//class History;

class Server{
    private:
            int                         port;
            int                         socketFd;
            std::string                 password;
            struct sockaddr_in          sockaddr; // выбрали из https://www.opennet.ru/docs/RUS/socket/node4.html
            std::vector<struct pollfd>  userPollFds;
            Config                      config;
            Operator                    oper;
            std::vector<std::string>	motd;
            std::vector<std::string>	info;
            std::string                 servername;
            std::vector<User *>		connectedUsers;
            Server();

    public:
            Server (int port, const std::string password);
            ~Server();

            int createSocket();
            void serverMagic();
            void executeLoop();
            void receiveMessage();
            int manageCommand(User &user);
            

};

#endif
