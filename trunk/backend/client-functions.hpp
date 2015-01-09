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

    ObjectPointer execute(VM& vm, arg_list const& args) const override
    {
        if (args.size() != 1)
            throw std::runtime_error("Argument count not valid");

        String* id = dynamic_cast<String*>(args[0].get());

        vm.startClient(id->getValue());

        return nullptr;
    }
};

class SetClientId : Function
{
public:
    SetClientId() : Function("setClientId")
    {
    }

    ObjectPointer execute(VM& vm, arg_list const& args) const override
    {
        if (args.size() != 1)
            throw std::runtime_error("Argument count not valid");

        String* id = dynamic_cast<String*>(args[0].get());

        Client& client = vm.getCurrentClient();
        client.clientId = id->getValue();

        return nullptr;
    }
};

class SetPosition : Function
{
public:
    SetPosition() : Function("setPosition")
    {
    }

    ObjectPointer execute(VM& vm, arg_list const& args) const override
    {
        if (args.size() != 1)
            throw std::runtime_error("Argument count not valid");

        String* pos = dynamic_cast<String*>(args[0].get());

        Client& client = vm.getCurrentClient();
        client.position = pos->getValue();

        return nullptr;
    }
};

#endif // CLIENT_FUNCTIONS_HPP_INCLUDED
