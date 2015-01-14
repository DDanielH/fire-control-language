#ifndef FIRE_FUNCTIONS_HPP_INCLUDED
#define FIRE_FUNCTIONS_HPP_INCLUDED

#include <stdexcept>
#include <fstream>
#include <memory>

#include "function.hpp"
#include "vm.hpp"
#include "list.hpp"

class SendPosition : public Function
{
public:
    SendPosition() : Function("sendPosition")
    { }

    ObjectPointer execute(VM& vm, arg_list const& args) const override
    {
        if (args.size() != 0)
            throw std::runtime_error("Argument count not valid");

        auto clientData = vm.getClientData();
        std::cout << "sendPosition(id = " << clientData.id
            << ", pos = " << clientData.position << ")\n";

        return nullptr;
    }
};

class SendPicture : public Function
{
public:
    SendPicture() : Function("sendPicture")
    { }

    ObjectPointer execute(VM& vm, arg_list const& args) const override
    {
        if (args.size() != 1)
            throw std::runtime_error("Argument count not valid");

        String* path = dynamic_cast<String*>(args[0].get());
        if (path == nullptr)
            throw std::runtime_error("Expected a <String> but got <" + toString(args[0]) + ">");

        auto clientData = vm.getClientData();
        std::cout << "sendPicture(id = " << clientData.id
            << ", pos = " << clientData.position
            << ", pic = " << path->getValue() << ")\n";

        return nullptr;
    }
};

class LoadStringList : public Function
{
public:
    LoadStringList(std::string const& name) : Function(name)
    { }

    ObjectPointer execute(VM& vm, arg_list const& args) const override
    {
        if (args.size() != 1)
            throw std::runtime_error("Argument count not valid");

        String* fileName = dynamic_cast<String*>(args[0].get());
        if (fileName == nullptr)
            throw std::runtime_error("Expected a <String> but got <" + toString(args[0]) + ">");

        std::ifstream file(fileName->getValue());
        if (!file)
            throw std::runtime_error("Could not open file <" + fileName->getValue() + ">");

        auto list = std::make_shared<List>();
        std::string line;
        while (std::getline(file, line))
        {
            auto lineString = std::make_shared<String>(line);
            list->add(lineString);
        }

        return list;
    }
};

class LoadPictures : public LoadStringList
{
public:
    LoadPictures() : LoadStringList("loadPictures")
    { }
};

class LoadPositions : public LoadStringList
{
public:
    LoadPositions() : LoadStringList("loadPositions")
    { }
};

#endif // FIRE_FUNCTIONS_HPP_INCLUDED
