#ifndef IO_FUNCTIONS_HPP_INCLUDED
#define IO_FUNCTIONS_HPP_INCLUDED

#include "function.hpp"

#include <iostream>

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
            std::cout << arg->toString();
        }
        std::cout << std::endl;

        return nullptr;
    }
};


#endif // IO-FUNCTIONS_HPP_INCLUDED
