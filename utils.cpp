#include "utils.hpp"

void loadfile(std::vector<std::string> *arr, std::string const &path)
{
    std::ifstream src(path);
    std::string		line;

    if (src.is_open())
	{
		while (std::getline(src, line))
			arr->push_back(line);
		src.close();
	}
    else
    {
        std::cout << RED << "ERROR: " << STOP << "can't open file(" << path << ").\n";
        exit(1); 
    }
}