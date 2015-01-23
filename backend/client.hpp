#ifndef CLIENT_H
#define CLIENT_H

#include <thread>
#include <string>

struct ClientData
{
    std::string id;
    std::string position;
    std::string superseed;
};

struct Client
{
    std::thread thread;
    ClientData data;
};

#endif // CLIENT_H
