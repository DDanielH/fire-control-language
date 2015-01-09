#ifndef CLIENT_FUNCTIONS_HPP_INCLUDED
#define CLIENT_FUNCTIONS_HPP_INCLUDED

#include "function.hpp"

#include "client.hpp"

class StartClient : Function
{
public:
    StartClient() : Function("startClient")
    {
    }

    void execute(VM& vm, arg_list const& args) const override
    {
        if (args.size() != 1)
            throw std::runtime_error("Argument count not valid");

        String* id = dynamic_cast<String*>(args[0].get());

        vm.startClient(id->getValue());
    }
};

class SetClientId : Function
{
public:
    SetClientId() : Function("setClientId")
    {
    }

    void execute(VM& vm, arg_list const& args) const override
    {
        if (args.size() != 1)
            throw std::runtime_error("Argument count not valid");

        String* id = dynamic_cast<String*>(args[0].get());

        Client& client = vm.getCurrentClient();
        client.clientId = id->getValue();
    }
};

class SetPosition : Function
{
public:
    SetPosition() : Function("setPosition")
    {
    }

    void execute(VM& vm, arg_list const& args) const override
    {
        if (args.size() != 1)
            throw std::runtime_error("Argument count not valid");

        String* pos = dynamic_cast<String*>(args[0].get());

        Client& client = vm.getCurrentClient();
        client.position = pos->getValue();
    }
};

#endif // CLIENT_FUNCTIONS_HPP_INCLUDED
