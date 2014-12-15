#ifndef FUNCTION_HPP_INCLUDED
#define FUNCTION_HPP_INCLUDED
#include <string>
#include <vector>
#include "object.hpp"
typedef std::vector<Object*> arg_list;

class Function
{
    private:
        std::string m_name;
    public:
        Function(std::string const& name)
        : m_name(name)
        {
        }
        virtual void execute(arg_list const& args) = 0;
};

#endif // FUNCTION_HPP_INCLUDED
