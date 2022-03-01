#ifndef USER_HPP
#define USER_HPP

#include "Server.hpp"
#include "utils.hpp"
#include <queue>

#define REGISTERED		0b00000001
#define INVISIBLE		0b00000010
#define RECEIVENOTICE	0b00000100
#define RECEIVEWALLOPS	0b00001000
#define IRCOPERATOR		0b00010000
#define AWAY			0b00100000
#define PINGING			0b01000000
#define BREAKCONNECTION	0b10000000

class User
{
    private:
        int                         sockfd;
        std::string                 password;
        std::string                 nickname;
        std::string                 username;
        std::string                 hostname;
        std::string                 servername;
        std::string                 realname;
        time_t                      timeRegistration;
        time_t                      timeLastMessage;
        time_t                      timePing;
        std::string                 awayMessage;
        std::string                 exitMessage;
        std::queue<std::string>     messages;
        unsigned char               flags;
        //std::vector<Channel *>     channels;

        User();
    public:
        User(int sockfd, const std::string &hostname, std::string &servername);

        int                               getSockfd() const;
        const std::string                 getPassword() const;
        const std::string                 getNickname() const;
        const std::string                 getUsername() const;
        const std::string                 getHostname() const;
        const std::string                 getServername() const;
        const std::string                 getRealname() const;
        time_t                      getTimeRegistration() const;
        time_t                      getTimeLastMessage() const;
        time_t                      getTimePing() const;
        const std::string                 getAwayMessage() const;
        const std::string                 getExitMessage() const;
        const std::queue<std::string>     getMessages() const;
        std::string                       getPrefix() const;
        unsigned char					  getFlags() const;
        void                              setPassword(std::string const &str);
        void                              setNickname(std::string const &str);
        void                              setUsername(std::string const &str);
        void                              setHostname(std::string const &str);
        void                              setRealname(std::string const &str);
        void	                          setAwayMessage(const std::string &msg);
        void	                          sendMessage(const std::string &msg) const;
        void	                          setExitMessage(const std::string &str);
        void						      setFlag(unsigned char flag);
        void	                          updateTimeLastMessage();
        void	                          updateTimePing();
        void	                          popMessage(); //delete?
        int		                          readMessage();


};

#endif