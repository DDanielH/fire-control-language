#ifndef FUNCTION_HPP_INCLUDED
#define FUNCTION_HPP_INCLUDED
#include <string>
#include <vector>
#include "object.hpp"

typedef std::vector<ObjectPointer> arg_list;

class Function
{
    private:
        std::string m_name;
    public:
        Function(std::string const& name)
        : m_name(name)
        {
        }
        virtual void execute(arg_list const& args) const = 0;
        std::string getName() { return m_name; }
};

class CountFunction : public Function
{
public:
    CountFunction() : Function("count")
    {
    }

    void execute(arg_list const& args) const override
    {

    }
};

#endif // FUNCTION_HPP_INCLUDED
