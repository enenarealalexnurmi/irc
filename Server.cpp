#include "Server.hpp"

Server::Server (int port, const std::string password):
port(port), password(password), oper(config.get("operatorName"), config.get("operatorPassword"))
{
    socketFd = createSocket();
    bzero(&sockaddr, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = htonl(INADDR_ANY); //allowedIP; //INADDR_ANY => 127.0.0.1
    sockaddr.sin_port = htons(port); /* https://russianblogs.com/article/8984813568/  */
    userPollFds.push_back(pollfd());
    userPollFds.back().fd = socketFd;
    userPollFds.back().events = POLLIN;
    loadfile(&motd, "./configs/motd.txt");
    loadfile(&info, "./configs/info.txt");
}

/*
int socket (int domain, int type, int protocol);
домен: AF_INET - адреса Internet Protocol v4
тип связи с сокетом: STREAM - для TCP, DGRAM - для UDP
протокол для канала связи: при 0 - ОС автоматически выбирает протокол
*/

int     Server::createSocket()
{
    int fd;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        std::cout << RED << "SERVER ERROR: " << STOP << "establishing soket error.\n"
        << errno << ": " << strerror(errno) << std::endl;
        exit(1);
    }
    std::cout << GREEN << "Socket was created successfully.\n" << STOP;
    return (fd);
}

void Server::serverMagic()
{
    int enable;

    enable = 1;
    if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0) //благодаря этому сокет может использовать порт повторно
    {
        std::cout << RED << "SERVER ERROR: " << STOP << "setsockopt failed.\n"
        << errno << ": " << strerror(errno) << std::endl;
        exit(1);
    }
    std::cout << GREEN << "Options for socket was settled successfully.\n" << STOP;
    /*if (fcntl(socketFd, F_SETFL, O_NONBLOCK) < 0) //ТРЕБОВАНИЕ ИЗ САБДЖЕКТА! установка сокета для неблокируемого ввода-вывода
    {
        std::cout << RED << "SERVER ERROR: " << STOP << "file controle (fcntl) failed.\n"
        << errno << ": " << strerror(errno) << std::endl;
        exit(1);
    }
    std::cout << GREEN << "Non-blocking mode for files was settled successfully.\n" << STOP;*/
    if (bind(socketFd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) //привязываем сокет к порту
    {
        std::cout << RED << "SERVER ERROR: " << STOP << "unable to bind to port.\n"
        << errno << ": " << strerror(errno) << std::endl;
        exit(1);
    }
    std::cout << GREEN << "Socket was binded successfully.\n" << STOP;
    if (listen(socketFd, 128) < 0) //задаем очередь 128 - можем слушать 128 клиентов
    {
        std::cout << RED << "SERVER ERROR: " << STOP << "unable to bind to port.\n"
        << errno << ": " << strerror(errno) << std::endl;
        exit(1); 
    }
    std::cout << GREEN << "Listening started successfully.\n" << STOP;

}

void Server::executeLoop()
{
    unsigned int        addressSize;
    int                 connectFd;
    
    addressSize = sizeof(sockaddr);
    connectFd = accept(socketFd, (struct sockaddr *)&sockaddr, &addressSize);
    if (connectFd < 0)
    {
        std::cout << RED << "SERVER ERROR: " << STOP << "can't open secondary socket.\n"
        << errno << ": " << strerror(errno) << std::endl;
        exit(1); 
    }
    userPollFds.push_back(pollfd());
    userPollFds.back().fd = socketFd;
    userPollFds.back().events = POLLIN;
    //connectedUsers.push_back(new User(connection, host, name));
    send(connectFd, "Hello word!\n", 12, 0);
    
}

void Server::closeSocket()
{
    if (socketFd)
        close(socketFd);
}

Server::~Server()
{
    std::cout << "Bye!\n";
}