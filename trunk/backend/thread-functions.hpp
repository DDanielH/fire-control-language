#ifndef THREAD_FUNCTIONS_HPP_INCLUDED
#define THREAD_FUNCTIONS_HPP_INCLUDED

#include <iostream>
#include <thread>

#include "function.hpp"
#include "vm.hpp"

class CountFunction : public Function
{
public:
    CountFunction() : Function("count")
    {
    }

    ObjectPointer execute(VM& vm, arg_list const& args) const override
    {
        if (args.size() != 2)
            throw std::runtime_error("Argument count not valid");

        Integer* sleepInMs = dynamic_cast<Integer*>(args[0].get());
        Integer* iterations = dynamic_cast<Integer*>(args[1].get());

        for (int i = 0; i < iterations->getValue(); ++i)
        {
            auto duration = std::chrono::milliseconds(sleepInMs->getValue());
            std::this_thread::sleep_for(duration);
            std::cout << "Iteration: " << i << std::endl;
        }

        return nullptr;
    }
};

class StartThread : public Function
{
public:
    StartThread() : Function("start")
    {
    }

    ObjectPointer execute(VM& vm, arg_list const& args) const override
    {
        if (args.size() != 2)
            throw std::runtime_error("Argument count not valid");

        String* name = dynamic_cast<String*>(args[0].get());
        String* id = dynamic_cast<String*>(args[1].get());

        vm.startThread(name->getValue(), id->getValue());

        return nullptr;
    }
};

class JoinThread : public Function
{
public:
    JoinThread() : Function("join")
    {
    }

    ObjectPointer execute(VM& vm, arg_list const& args) const override
    {
        if (args.size() != 1)
            throw std::runtime_error("Argument count not valid");

        String* id = dynamic_cast<String*>(args[0].get());

        vm.joinThread(id->getValue());

        return nullptr;
    }
};

class WaitThread : public Function
{
public:
    WaitThread() : Function("wait")
    {
    }

    ObjectPointer execute(VM& vm, arg_list const& args) const override
    {
        if (args.size() != 1)
            throw std::runtime_error("Argument count not valid");

        Integer* sleepInMs = dynamic_cast<Integer*>(args[0].get());

        auto duration = std::chrono::milliseconds(sleepInMs->getValue());
        std::this_thread::sleep_for(duration);

        return nullptr;
    }
};


#endif // THREAD_FUNCTIONS_HPP_INCLUDED
