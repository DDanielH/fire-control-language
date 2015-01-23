#include "fire_adapter.h"
#include <iostream>

FireAdapter::FireAdapter()
{
}

void FireAdapter::startMission(std::string dep_file)
{
    std::cout << "start Mission: " <<dep_file<<"\n";
}
void FireAdapter::sendLocation(std::string cid, std::string loc)
{
    std::cout << "send Location: " <<cid<< " loc: "<< loc << "\n";
}
void FireAdapter::sendPicture(std::string cid, std::string loc,std::string  pic)
{
    std::cout << "send Picture: " <<cid<< " loc: "<< loc << " pic: "<< pic <<"\n";
}

void FireAdapter::sendMessage(std::string client_id, std::string location, std::string module, std::string message_type, std::string content)
{
    std::cout << "send Message: " <<client_id<< " loc: "<< location << " mod: "<< module <<" msgtype: "<< message_type <<" cont: "<< content <<"\n";

}
