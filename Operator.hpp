#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include <iostream>

class Operator
{
    private:
        std::string name;
        std::string password;

    public:
        Operator();
        Operator(std::string operatorName, std::string password);
        
        std::string getName();
        std::string getPassword();
};

#endif