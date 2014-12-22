#include "context.hpp"

void Context::pushInteger(int value)
{
    auto i = std::make_shared<Integer>(value);
    m_stack.push(i);
}

void Context::pushString(std::string value)
{
    auto s = std::make_shared<String>(value);
    m_stack.push(s);
}

void Context::call(std::string name, int argCount)
{
    auto& func = m_vm.getFunctionByName(name);
    arg_list argList;
    for (int i = 0; i < argCount; i++)
    {
        // das erste Element liegt unten...
        argList.insert(argList.begin() ,m_stack.top());
        m_stack.pop();
    }
    func.execute(argList);
}
