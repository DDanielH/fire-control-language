#include "fire_adapter.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
//#include <regex>
#include "fire_exception.h"

FireAdapter::FireAdapter()
{

}

void FireAdapter::startMission(std::string depesche_file)
{
    std::string cmd = "curl --silent --form xml=@" + depesche_file + " 'mission.fire.faryu.de/local/deployment.php'";
    //std::cout << cmd << std::endl;
    std::string res = exec(cmd.c_str());
    if (res.empty())
        throw FireException("Deployment failed!");

    //std::cout << res << std::endl;
    m_missionId = res;
}

std::string FireAdapter::sendLocation(std::string client_id, std::string location, std::string superseed)
{
    std::string cmd = "curl --silent -F \"mission_id=" + m_missionId + "\" -F \"client_id=" + client_id + "\"";
    cmd += " -F \"module=GPTR\"";
    cmd += " -F \"msg_type=GPOS\"";
    cmd += " -F \"priority=5\"";

    if (location.empty())
        throw FireException("Location cannot be empty!");

    std::vector<std::string> coords = split(location, ',');
    if (coords.size() != 2)
        throw FireException("Invalid location format! " + location);

    if (!superseed.empty())
        cmd += " -F \"superseed=" + superseed + "\"";

    cmd += " -F \"lon=" + coords[0] + "\"";
    cmd += " -F \"lat=" + coords[1] + "\"";
    cmd += " 'mission.fire.faryu.de/local/fcl_message_save.php'";
    std::cout << cmd << std::endl;
    std::string res = exec(cmd.c_str());
    std::cout << res << std::endl;
    return res;
}

void FireAdapter::sendPicture(std::string client_id, std::string location, std::string picture_file)
{

    std::string cmd = "curl --silent -F \"mission_id=" + m_missionId + "\" -F \"client_id=" + client_id + "\"";

    /*std::smatch sm;
    bool matches = std::regex_match (location, sm, std::regex("(-?[0-9]+\\.[0-9]+),(-?[0-9]+\\.[0-9]+)"));*/
    if (!location.empty())
    {
        /*if (sm.size() == 3)
        {
            std::string lon = sm[1];
            std::string lat = sm[2];
            cmd += " -F \"lon=" + lon + "\"";
            cmd += " -F \"lat=" + lat + "\"";
        }*/
        std::vector<std::string> coords = split(location, ',');
        if (coords.size() == 2)
        {
            cmd += " -F \"lon=" + coords[0] + "\"";
            cmd += " -F \"lat=" + coords[1] + "\"";
        }
    }
    cmd += " -F \"uploadedfile=@" + picture_file + "\" 'mission.fire.faryu.de/local/fcl_upload_image.php'";
    std::cout << cmd << std::endl;
    std::string res = exec(cmd.c_str());
    std::cout << res << std::endl;
}

std::string FireAdapter::sendMessage(std::string client_id, std::string location, std::string module, std::string message_type, std::string superseed, std::string priority, std::string content)
{
    std::string cmd = "curl --silent -F \"mission_id=" + m_missionId + "\" -F \"client_id=" + client_id + "\"";
    cmd += " -F \"module=" + module + "\"";
    cmd += " -F \"msg_type=" + message_type + "\"";
    cmd += " -F \"priority=" + priority + "\"";

    if (!superseed.empty())
        cmd += " -F \"superseed=" + superseed + "\"";

    if (!location.empty())
    {
        std::vector<std::string> coords = split(location, ',');
        if (coords.size() != 2)
        {
            cmd += " -F \"lon=" + coords[0] + "\"";
            cmd += " -F \"lat=" + coords[1] + "\"";
        }
    }

    if (!content.empty())
        cmd += " -F \"content=" + content + "\"";
    cmd += " 'mission.fire.faryu.de/local/fcl_message_save.php'";
    std::cout << cmd << std::endl;
    std::string res = exec(cmd.c_str());
    std::cout << res << std::endl;
    return res;
}

std::string FireAdapter::exec(const char* cmd)
{
   FILE* pipe = popen(cmd, "r");
   if (!pipe)
       return ERROR_PIPE;

   char buffer[128];
   std::string result = "";
   while(!feof(pipe)) {
       if(fgets(buffer, 128, pipe) != NULL)
           result += buffer;
   }
   pclose(pipe);
   return result;
}

std::vector<std::string> FireAdapter::split(std::string str, const char delim)
{
    std::vector<std::string> parts;
    if(str.empty())
        return parts;

    std::istringstream f(str);
    std::string s;
    while (getline(f, s, delim)) {
        parts.push_back(s);
    }
    return parts;
}
