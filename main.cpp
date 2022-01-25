#include "Server.hpp"
#include "stdio.h"
#include "string.h"

bool gate = true;
/*Все порты разделены на три диапазона — общеизвестные (или системные, 0—1023),
зарегистрированные (или пользовательские, 1024—49151)
и динамические (или частные, 49152—65535). */
int checkPort(char *port)
{
    unsigned int len;
    int          number;
    int i;

    len = strlen(port);
    if (len < 3 || len > 5)
        return 1;
    for (i = 0; i < len; i++)
        if (port[i] < '0' || port[i] > '9')
        return 1;
    number = atoi(port);
    if (number < 1024 || number > 49151)
        return 1;
    return 0;
}

void handleShutdown(int sig)
{
    gate = false;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cout << RED << "WARNING!" << STOP
        << "Usage: ./ircserv <port> <password>" << std::cout;
        return 1;
    }
    if (checkPort(argv[1]) == 1)
    {
        std::cout << RED << "ERROR:" << STOP
        << "wrong port." << std::cout;
        return 1;
    }
    Server irc(atoi(argv[1]), argv[2]);
    irc.serverMagic();
    
    signal(SIGINT, handleShutdown);
    while (gate)
        irc.execute();
    irc.closeSocket();
    return (0);
}