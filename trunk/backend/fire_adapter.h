#ifndef FIRE_ADAPTER_H
#define FIRE_ADAPTER_H

#include <string>

class FireAdapter
{
public:
    FireAdapter();

    void startMission(std::string depesche_file) {}
    void sendLocation(std::string client_id, std::string location) {}
    void sendPicture(std::string client_id, std::string location, std::string picture_file) {}
    void sendMessage(std::string client_id, std::string location, std::string module, std::string message_type, std::string content) {}
};

#endif // FIRE_ADAPTER_H
