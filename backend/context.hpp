#ifndef CONTEXT_HPP_INCLUDED
#define CONTEXT_HPP_INCLUDED
#include <string>


class Context
{
public:
    void pushInteger(int value);
    void pushString(std::string value);
    void call(std::string name, int argCount);
};


#endif // CONTEXT_HPP_INCLUDED
