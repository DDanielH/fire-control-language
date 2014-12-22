#include "context.hpp"

void Context::pushInteger(int value)
{
    Integer i(value);
    m_stack.push(i);
}

void Context::pushString(std::string value)
{
    String s(value);
    m_stack.push(s);
}

void Context::call(std::string name, int argCount)
{
    // das erste Element liegt unten...
}
