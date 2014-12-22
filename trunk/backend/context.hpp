#ifndef CONTEXT_HPP_INCLUDED
#define CONTEXT_HPP_INCLUDED
#include <string>
#include <stack>
#include "object.hpp"
#include "vm.hpp"
#include "function.hpp"

class Context
{
private:
    std::stack<ObjectPointer> m_stack;
    VM& m_vm;

public:
    Context(VM& vm)
        :m_vm(vm)
    {
    }


    void pushInteger(int value);
    void pushString(std::string value);
    void call(std::string name, int argCount);
};


#endif // CONTEXT_HPP_INCLUDED
