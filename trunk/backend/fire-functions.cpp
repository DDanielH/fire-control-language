#include "fire-functions.hpp"
#include <thread>
#include <mutex>

FireAdapter fireAdapter;
std::mutex  fireMutex;

typedef std::lock_guard<std::mutex> scoped_lock;

ObjectPointer StartMission::execute(VM& vm, arg_list const& args)const
 {
        if (args.size() != 1)
            throw std::runtime_error("Argument count not valid");

        String* path = dynamic_cast<String*>(args[0].get());
        if (path == nullptr)
            throw std::runtime_error("Expected a <String> but got <" + toString(args[0]) + ">");

        scoped_lock lock(fireMutex);
        fireAdapter.startMission(path->getValue());

        return nullptr;
}


  ObjectPointer SendPicture::execute(VM& vm, arg_list const& args) const
    {
        if (args.size() != 1)
            throw std::runtime_error("Argument count not valid");

        String* path = dynamic_cast<String*>(args[0].get());
        if (path == nullptr)
            throw std::runtime_error("Expected a <String> but got <" + toString(args[0]) + ">");

        auto clientData = vm.getClientData();


        scoped_lock lock(fireMutex);
        fireAdapter.sendPicture(clientData.id,clientData.position,path->getValue());


        return nullptr;
    }


ObjectPointer SendPosition::execute(VM& vm, arg_list const& args) const
    {
        if (args.size() != 0)
            throw std::runtime_error("Argument count not valid");

        auto clientData = vm.getClientData();

        scoped_lock lock(fireMutex);
        std::string superseed = fireAdapter.sendLocation(clientData.id,clientData.position,clientData.superseed);
        clientData.superseed = superseed;
        vm.setClientData(clientData);

        return nullptr;
    }
ObjectPointer SendMessage::execute(VM& vm, arg_list const& args) const
{
    if (args.size() != 3)
        throw std::runtime_error("Argument count not valid");

    String* module = dynamic_cast<String*>(args[0].get());
    if (module == nullptr)
        throw std::runtime_error("Expected a <String> but got <" + toString(args[0]) + ">");
    String* msgType = dynamic_cast<String*>(args[1].get());
    if (msgType == nullptr)
        throw std::runtime_error("Expected a <String> but got <" + toString(args[1]) + ">");
    String* content = dynamic_cast<String*>(args[2].get());
    if (content == nullptr)
        throw std::runtime_error("Expected a <String> but got <" + toString(args[2]) + ">");

    auto clientData = vm.getClientData();

    scoped_lock lock(fireMutex);
    fireAdapter.sendMessage(clientData.id,clientData.position,module->getValue(),msgType->getValue(),"","5",content->getValue());

    return nullptr;
}
