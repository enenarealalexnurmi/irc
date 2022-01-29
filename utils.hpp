#ifndef UTILS_HPP
#define UTILS_HPP

#define RED		"\x1b[31m"
#define GREEN		"\x1b[32m"
#define LIGHT_BLUE	"\x1b[34m"
#define GRAY		"\x1b[90m"
#define YELLOW		"\x1b[33m"
#define PINK		"\x1b[35m"
#define STOP		"\x1b[0m"

#include <iostream>
#include <fstream>
#include <vector>

void loadfile(std::vector<std::string> *arr, std::string const &path);
#endif