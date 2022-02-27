#include "Server.hpp"

Server::Server (int port, const std::string password):
port(port), password(password), oper(config.get("operatorName"), config.get("operatorPassword")), servername(config.get("servername"))
{
    socketFd = createSocket();
    bzero(&sockaddr, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = htonl(INADDR_ANY); //allowedIP; //INADDR_ANY => 127.0.0.1
    sockaddr.sin_port = htons(port); /* https://russianblogs.com/article/8984813568/  */
    //userPollFds.push_back(pollfd());
    //userPollFds.back().fd = socketFd;
    //userPollFds.back().events = POLLIN;
   // userPollFds.back().revents = 0;
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
        std::cout << RED << "SERVER ERROR: " << STOP << "establishing soket error.\n";
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
        std::cout << RED << "SERVER ERROR: " << STOP << "setsockopt failed.\n";
        exit(1);
    }
    std::cout << GREEN << "Options for socket was settled successfully.\n" << STOP;
    if (bind(socketFd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) //привязываем сокет к порту
    {
        std::cout << RED << "SERVER ERROR: " << STOP << "unable to bind to port.\n";
        exit(1);
    }
    std::cout << GREEN << "Socket was binded successfully.\n" << STOP;
    if (listen(socketFd, 128) < 0) //задаем очередь 128 - можем слушать 128 клиентов
    {
        std::cout << RED << "SERVER ERROR: " << STOP << "unable to bind to port.\n";
        exit(1); 
    }
    std::cout << GREEN << "Listening started successfully.\n" << STOP;
    if (fcntl(socketFd, F_SETFL, O_NONBLOCK) < 0) //ТРЕБОВАНИЕ ИЗ САБДЖЕКТА! установка сокета для неблокируемого ввода-вывода
    {
        std::cout << RED << "SERVER ERROR: " << STOP << "file controle (fcntl) failed.\n";
        //<< errno << ": " << strerror(errno) << std::endl;
        exit(1);
    }
    std::cout << GREEN << "Non-blocking mode for files was settled successfully.\n" << STOP;

}

void Server::executeLoop()
{
    unsigned int        addressSize;
    int                 connectFd;
    char                host[16];
    
    addressSize = sizeof(sockaddr);
    connectFd = accept(socketFd, (struct sockaddr *)&sockaddr, &addressSize);
    if (connectFd >= 0)
    {
    inet_ntop(AF_INET, &(sockaddr.sin_addr), host, 16);
    userPollFds.push_back(pollfd());
    userPollFds.back().fd = connectFd;
    userPollFds.back().events = POLLIN;
    userPollFds.back().revents = 0;
    connectedUsers.push_back(new User(connectFd, host, servername));
    send(connectFd, "Hello word!\n", 12, 0);
    }
    receiveMessage();
    //pingMonitor();
}

void Server::receiveMessage() //Тут не работает!!!
{
    int pret;
    int ping;
    size_t i;
    int ret;

    ping = atoi(config.get("ping").c_str());
    pret = poll(&userPollFds[0], userPollFds.size(), (ping * 1000)/10);
    std::cout << "size: " << userPollFds.size() << "; ping timeout: " << (ping *1000) /10 << std::endl;
    if (pret == -1)
        return ;
    if (pret != 0)
    {
        for (i = 0; i < userPollFds.size(); i++)
        {
            if (userPollFds[i].revents == POLLIN)
            {
                ret = connectedUsers[i]->readMessage();
                if (ret >= 0)
                   manageCommand(*(connectedUsers[i])); //else -> delete User
            }
            userPollFds[i].revents = 0;
        }
    }
}

int Server::manageCommand(User &user)
{

    //пользователь зарегестрирован?
    //да -> команда есть?
      //да -> выполнить команду
      //нет -> вывод ошибки
    //нет -> вывод ошибки
    user.updateTimefLastMessage();
	return (0);
}

Server::~Server()
{  
    printf("Bye!\n");
}