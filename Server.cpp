#include "Server.hpp"

Server::Server (int port, const std::string password):
port(port), password(password)
{
    socketFd = createSocket();
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
    if (fd < 0)
    {
        std::cout << RED << "SERVER ERROR: " << STOP << "establishing soket error.\n";
        exit(1);
    }
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY; //allowedIP; //INADDR_ANY => 127.0.0.1
    sockaddr.sin_port = htons(port); /* https://russianblogs.com/article/8984813568/  */
    return (fd);
}

void Server::serverMagic()
{
    int enable;

    enable = 1;
    if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
    {
        std::cout << RED << "SERVER ERROR: " << STOP << "setsockopt failed.\n";
        exit(1);
    }
    if (fcntl(socketFd, F_SETFL, O_NONBLOCK) < 0) //установка сокета для неблокируемого ввода-вывода
    {
        std::cout << RED << "SERVER ERROR: " << STOP << "file controle (fcntl) failed.\n";
        exit(1);
    }
    if (bind(socketFd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) //привязываем сокет к порту
    {
        std::cout << RED << "SERVER ERROR: " << STOP << "unable to bind to port.\n";
        exit(1);
    }
    if (listen(socketFd, 128) < 0) //задаем очередь 128 - можем слушать 128 клиентов
    {
        std::cout << RED << "SERVER ERROR: " << STOP << "unable to bind to port.\n";
        exit(1); 
    }
}

void Server::execute()
{
    unsigned int addressSize;
    int connectFd;
    
    addressSize = sizeof(sockaddr);
    connectFd = accept(socketFd, (struct sockaddr *)&sockaddr, &addressSize);
    if (connectFd < 0)
    {
        std::cout << RED << "SERVER ERROR: " << STOP << "can't open secondary socket.\n";
        exit(1); 
    }

}

void Server::closeSocket()
{
    if (socketFd)
        close(socketFd);
}




