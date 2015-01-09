#ifndef CLIENT_H
#define CLIENT_H

#include <thread>
#include <string>
#include <memory>

struct Client
{
    std::shared_ptr<std::thread> thread;
    std::string clientId;
    std::string position;
};

#endif // CLIENT_H
