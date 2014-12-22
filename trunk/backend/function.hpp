#ifndef FUNCTION_HPP_INCLUDED
#define FUNCTION_HPP_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include "object.hpp"
#include "vm.hpp"

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
        virtual void execute(VM& vm, arg_list const& args) const = 0;
        std::string getName() { return m_name; }
};

class CountFunction : public Function
{
public:
    CountFunction() : Function("count")
    {
    }

    void execute(VM& vm, arg_list const& args) const override
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
    }
};

class StartThread : public Function
{
public:
    StartThread() : Function("start")
    {
    }

    void execute(VM& vm, arg_list const& args) const override
    {
        if (args.size() != 2)
            throw std::runtime_error("Argument count not valid");

        String* name = dynamic_cast<String*>(args[0].get());
        String* id = dynamic_cast<String*>(args[1].get());

        vm.startThread(name->getValue(), id->getValue());
    }
};

class JoinThread : public Function
{
public:
    JoinThread() : Function("join")
    {
    }

    void execute(VM& vm, arg_list const& args) const override
    {
        if (args.size() != 1)
            throw std::runtime_error("Argument count not valid");

        String* id = dynamic_cast<String*>(args[0].get());

        vm.joinThread(id->getValue());
    }
};

#endif // FUNCTION_HPP_INCLUDED
