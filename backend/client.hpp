#ifndef CLIENT_H
#define CLIENT_H

#include <thread>
#include <string>

struct ClientData
{
    std::string id;
    std::string position;
};

struct Client
{
    std::thread thread;
    ClientData data;
};

#endif // CLIENT_H
