#ifndef CLIENT_H
#define CLIENT_H

#include <thread>
#include <string>

struct Client
{
    std::thread thread;
    std::string clientId;
    std::string position;
};

#endif // CLIENT_H
