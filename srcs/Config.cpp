#include "Config.hpp"

Config::Config()
{
    init("./configs/default.config");
}

void Config::init(std::string pathToConfig)
{
    std::string delimiter = "=";
    size_t position;
    std::string line;
    std::ifstream ifs(pathToConfig.c_str(), std::ifstream::in);
    if (!ifs.good())
    {
        std::cout << RED << "ERROR: " << STOP << "can't open configs-file.\n";
        exit(1);
    }
    while(!ifs.eof())
    {
        line = "";
        std::getline(ifs, line);
        if ((position = line.find('=')) == std::string::npos)
            continue;
        std::string key = line.substr(0, position);
        line.erase(0, position + delimiter.length());
        values[key] = line;
    }
    ifs.close();
        
}

void Config::set(std::string key, std::string value)
{
    values[key] = value;
}

std::string Config::get(std::string key)
{
    return values[key];
}

void Config::reread()
{
    values.clear();
    init("./configs/default.config");
}