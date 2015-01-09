#include "context.hpp"

void Context::declareVar(std::string const& name)
{
    if (m_stack.empty())
        throw std::runtime_error("No value in variable declaration");

    m_vars[name] = m_stack.top();
    m_stack.pop();
}

void Context::pushInteger(int value)
{
    auto i = std::make_shared<Integer>(value);
    m_stack.push(i);
}

void Context::pushString(std::string const& value)
{
    auto s = std::make_shared<String>(value);
    m_stack.push(s);
}

void Context::pushVar(std::string const& name)
{
    auto value = m_vars.find(name);
    if (value == m_vars.end())
        throw std::runtime_error("Variable <" + name + "> was not declared");

    m_stack.push(value->second);
}

void Context::pop()
{
    m_stack.pop();
}

void Context::call(std::string name, int argCount)
{
    auto& func = m_vm.getFunctionByName(name);
    arg_list argList;
    for (int i = 0; i < argCount; i++)
    {
        // das erste Element liegt unten...
        argList.push_back(m_stack.top());
        m_stack.pop();
    }
    auto returnValue = func.execute(m_vm, argList);
    m_stack.push(returnValue);
}

void Context::foreach(std::string const& varName, std::string const& listName)
{
    // Liste holen
    // Über Liste iterieren
    // Bei jedem Durchlauf varName auf Wert in Liste setzen
}
