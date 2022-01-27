#ifndef CONFIG_HPP
#define CONFIG_HPP

# define RED		"\x1b[31m"
# define STOP		"\x1b[0m"

#include <iostream>
#include <string>
#include <map>
//#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>

//std::string currentTime();
//void error(std::string message, bool gate);
//std::vector<std::string> split(std::string str, std::string delimiter);
//bool isLetter(char c);
//bool isSpecial(char c);
//bool isDigit(char c);
//std::string toString(size_t var);
//bool strmatch(std::string str, std::string pattern);

class Config
{
    private:
            std::map<std::string, std::string> values;

            void init(std::string pathToConfig);
    
    public:
            Config();
            Config(std::string pathToConfig);

            void set(std::string key, std::string value);
            std::string get(std::string key);
};

#endif