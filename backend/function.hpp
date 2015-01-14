#ifndef FUNCTION_HPP_INCLUDED
#define FUNCTION_HPP_INCLUDED

#include <string>
#include <vector>

#include "object.hpp"

class VM;

typedef std::vector<ObjectPointer> arg_list;

class Function
{
private:
    std::string m_name;
public:
    Function(std::string const& name)
    : m_name(name)
    { }

    virtual ObjectPointer execute(VM& vm, arg_list const& args) const = 0;

    std::string const& getName() const { return m_name; }
};

#endif // FUNCTION_HPP_INCLUDED
