#ifndef VM_HPP_INCLUDED
#define VM_HPP_INCLUDED

#include <string>
#include <thread>
#include <map>
#include <memory>
#include <mutex>
#include "client.hpp"

class ThreadListNode;
class ThreadNode;
class ClientListNode;
class ClientNode;
class Function;

typedef std::shared_ptr<Client> ClientPointer;


class VM
{
private:
    std::map<std::string, std::shared_ptr<std::thread>> m_runningThreads;
    std::map<std::string, ThreadNode const*> m_threadNodes;
    std::map<std::string, ClientNode const*> m_clientNodes;
    std::map<std::string, std::shared_ptr<Function>> m_functionList;
    std::map<std::string, ClientPointer> m_clients;
    std::mutex m_runningThreadMutex;
    std::mutex m_functionsMutex;
    std::mutex m_clientsMutex;
    std::mutex m_clientDataMutex;

private:
    void joinAllThreads();
    void joinAllClients();

public:
    void startThread(std::string const& name, std::string const& id);
    void joinThread(std::string const& id);
    void registerThreads(ThreadListNode const* threadList);
    void registerClients(ClientListNode const* clientList);
    void shutdown();

    void registerFunction(std::shared_ptr<Function> const& function);
    Function const& getFunctionByName(std::string const& name);

    void startClient(std::string const& clientName);
    ClientData getClientData();
    void setClientData(ClientData const& data);
};


#endif // VM_HPP_INCLUDED
