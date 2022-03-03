#include "../hdrs/Operator.hpp"

Operator::Operator()
{
    name = "admin";
    password = "admin";
    std::cout << "Oper ctor" << std::endl;
}

Operator::Operator(std::string operatorName, std::string operatorPassword)
{
    name = operatorName;
    password = operatorPassword;
}
        
std::string Operator::getName()
{
    return name;
}

std::string Operator::getPassword()
{
    return password;
}