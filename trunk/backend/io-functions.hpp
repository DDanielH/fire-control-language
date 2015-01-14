#ifndef IO_FUNCTIONS_HPP_INCLUDED
#define IO_FUNCTIONS_HPP_INCLUDED

#include <iostream>

#include "function.hpp"

class WriteLine : public Function
{
public:
    WriteLine() : Function("writeLine")
    {
    }

    ObjectPointer execute(VM& vm, arg_list const& args) const override
    {
        for (auto& arg : args)
        {
            std::cout << toString(arg);
        }
        std::cout << std::endl;

        return nullptr;
    }
};


#endif // IO_FUNCTIONS_HPP_INCLUDED
