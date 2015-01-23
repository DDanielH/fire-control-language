#ifndef FIRE_ADAPTER_H
#define FIRE_ADAPTER_H

#include <string>
#include <vector>

#define ERROR_PIPE "ERROR"

class FireAdapter
{
public:
    FireAdapter();

    void startMission(std::string depesche_file);
    std::string sendLocation(std::string client_id, std::string location, std::string superseed);
    void sendPicture(std::string client_id, std::string location, std::string picture_file);
    std::string sendMessage(std::string client_id, std::string location, std::string module, std::string message_type, std::string superseed, std::string priority, std::string content);

    static std::string exec(const char* cmd);
    static std::vector<std::string> split(std::string str, const char delim);

private:
    std::string m_missionId;
};

#endif // FIRE_ADAPTER_H
