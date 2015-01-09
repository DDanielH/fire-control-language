#ifndef FUNCTION_HPP_INCLUDED
#define FUNCTION_HPP_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include "object.hpp"
#include "vm.hpp"
#include "list.hpp"

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
        virtual ObjectPointer execute(VM& vm, arg_list const& args) const = 0;
        std::string getName() { return m_name; }
};

#endif // FUNCTION_HPP_INCLUDED
