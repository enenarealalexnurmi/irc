#include "Server.hpp"
#include "stdio.h"
#include "string.h"
#include <signal.h>


int gate;
/*Все порты разделены на три диапазона — общеизвестные (или системные, 0—1023),
зарегистрированные (или пользовательские, 1024—49151)
и динамические (или частные, 49152—65535). */
int checkPort(char *port)
{
    unsigned int len;
    int number;
    unsigned int i;

    len = strlen(port);
    if (len < 4 || len > 5)
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
    std::ifstream src("./configs/parting.txt");
    std::string		line;


    (void)sig;
    close(gate); //во избежание заполнения портов надо закрывать сокеты
    std::cout << "\b\b" << PINK;
    if (src.is_open())
	{
		while (std::getline(src, line))
			std::cout << line << std::endl;
		src.close();
	}
    std::cout << STOP;
    exit(0);
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cout << RED << "WARNING! " << STOP
        << "Usage: ./ircserv <port> <password>\n" ;
        return 1;
    }
    if (checkPort(argv[1]) == 1)
    {
        std::cout << RED << "ERROR: " << STOP
        << "wrong port.\n";
        return 1;
    }
    Server irc(atoi(argv[1]), argv[2]);
    irc.serverMagic();
    std::cout << "Waiting for a connection...\n";
    signal(SIGINT, handleShutdown);
    while (gate >= 0)
    {
        irc.executeLoop();
        //gate = -2;
    }
    return 0;
}