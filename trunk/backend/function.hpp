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

class GetType : public Function
{
public:
    GetType() : Function("getType")
    {
    }

    ObjectPointer execute(VM& vm, arg_list const& args) const override
    {
        if (args.size() != 1)
            throw std::runtime_error("Argument count not valid");

        if (dynamic_cast<Boolean*>(args[0].get()) != nullptr)
            return std::make_shared<String>("Boolean");
        if (dynamic_cast<Integer*>(args[0].get()) != nullptr)
            return std::make_shared<String>("Integer");
        if (dynamic_cast<String*>(args[0].get()) != nullptr)
            return std::make_shared<String>("String");

        return std::make_shared<String>("Object");
    }
};

class SendPosition : public Function
{
public:
    SendPosition() : Function("sendPosition")
    {
    }

    ObjectPointer execute(VM& vm, arg_list const& args) const override
    {
        if (args.size() != 0)
            throw std::runtime_error("Argument count not valid");

        Client& thisClient = vm.getCurrentClient();
        std::cout << "SendPosition call: clientId:" << thisClient.clientId << "position:" << thisClient.position << std::endl;
        return nullptr;
    }
};

class SendPicture : public Function
{
public:
    SendPicture() : Function("sendPicture")
    {
    }

    ObjectPointer execute(VM& vm, arg_list const& args) const override
    {
        if (args.size() != 1)
            throw std::runtime_error("Argument count not valid");

        Client& thisClient = vm.getCurrentClient();
        std::cout << "SendPicture call: clientId:" << thisClient.clientId << "position:" << thisClient.position << " picturePath:" << args[0].get() << std::endl;
        return nullptr;
    }
};

class LoadPicture : public Function
{
public:
    LoadPicture() : Function("loadPicture")
    {
    }

    ObjectPointer execute(VM& vm, arg_list const& args) const override
    {
        if (args.size() != 1)
            throw std::runtime_error("Argument count not valid");

        String* name = dynamic_cast<String*>(args[0].get());
        std::cout << name->getValue() << std::endl;

        List myList;
        std::string line;
        std::ifstream myfile (name->getValue());
        if (myfile.is_open())
        {
            while ( std::getline (myfile,line) )
            {
                //std::cout << line << '\n';
                auto s = std::make_shared<String>(line);
                myList.add(s);
            }
            myfile.close();
        }
        else
            std::cout << "Unable to open file";

        return std::make_shared<List>(myList);
    }
};

class LoadPosition : public Function
{
public:
    LoadPosition() : Function("loadPosition")
    {
    }

    ObjectPointer execute(VM& vm, arg_list const& args) const override
    {
        if (args.size() != 1)
            throw std::runtime_error("Argument count not valid");

        String* name = dynamic_cast<String*>(args[0].get());
        std::cout << name->getValue() << std::endl;

        List myList;
        std::string line;
        std::ifstream myfile (name->getValue());
        if (myfile.is_open())
        {
            while ( std::getline (myfile,line) )
            {
                //std::cout << line << '\n';
                auto s = std::make_shared<String>(line);
                myList.add(s);
            }
            myfile.close();
        }
        else
            std::cout << "Unable to open file";

        return std::make_shared<List>(myList);
    }
};

#endif // FUNCTION_HPP_INCLUDED
