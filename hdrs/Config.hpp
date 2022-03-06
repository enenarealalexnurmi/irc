#ifndef CONFIG_HPP
#define CONFIG_HPP

# define RED		"\x1b[31m"
# define STOP		"\x1b[0m"

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string.h>


class Config
{
    private:
            std::map<std::string, std::string> values;

            void init(std::string pathToConfig);
    
    public:
            Config();

            void set(std::string key, std::string value);
            std::string get(std::string key);
            void reread();
};

#endif