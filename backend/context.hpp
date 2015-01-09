#ifndef CONTEXT_HPP_INCLUDED
#define CONTEXT_HPP_INCLUDED

#include <string>
#include <stack>
#include <map>

#include "object.hpp"
#include "vm.hpp"
#include "function.hpp"

class Context
{
private:
    std::stack<ObjectPointer> m_stack;
    std::map<std::string, ObjectPointer> m_vars;
    VM& m_vm;

public:
    Context(VM& vm)
        :m_vm(vm)
    {
    }

    void declareVar(std::string const& name);

    void pushInteger(int value);
    void pushString(std::string const& value);
    void pushVar(std::string const& name);

    void pop();

    void call(std::string name, int argCount);
};


#endif // CONTEXT_HPP_INCLUDED
