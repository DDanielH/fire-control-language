#include "vm.hpp"
#include "context.hpp"
#include "function.hpp"

#include "../frontend/nodes.hpp"

thread_local client_ptr myClient;

typedef std::lock_guard<std::mutex> scoped_lock;

void VM::startThread(std::string const& name, std::string const& id)
{
    auto threadNode = m_threadNodes.find(name);
    if(threadNode == m_threadNodes.end())
        throw std::runtime_error("Thread not found: "+ name);

    scoped_lock lock(m_runningThreadMutex);
    auto runnningThread = m_runningThreads.find(id);
    if(runnningThread != m_runningThreads.end())
        throw std::runtime_error("Thread with id already started: "+ id);

    m_runningThreads[id] = std::make_shared<std::thread>([this, threadNode]{
       Context context(*this);
       threadNode->second->execute(&context);
    });
}


void VM::registerThreads(ThreadListNode const* threadList)
{
    for(auto& threadNode:threadList->getThreads())
    {
        m_threadNodes[threadNode->getName()] = threadNode.get();
    }
}
void VM::joinThread(std::string const& id)
{
    std::shared_ptr<std::thread> thread;
    {
        scoped_lock lock(m_runningThreadMutex);
        auto runnningThread = m_runningThreads.find(id);
        if(runnningThread != m_runningThreads.end())
            throw std::runtime_error("Thread not found: "+ id);
        thread = runnningThread->second;
    }
    thread->join();
    {
        scoped_lock lock(m_runningThreadMutex);
        m_runningThreads.erase(id);
    }
}

void VM::joinAllThreads()
{
    std::map<std::string,std::shared_ptr<std::thread>> runningThreads;
    {
        scoped_lock lock(m_runningThreadMutex);
        runningThreads = m_runningThreads;
    }
    for (auto& thread : runningThreads)
    {
        thread.second->join();
    }
    scoped_lock lock(m_runningThreadMutex);
    m_runningThreads.clear();
}

void VM::registerFunction(std::shared_ptr<Function> const& function)
{
    m_functionList.emplace(function->getName(), function);
}

Function const& VM::getFunctionByName(std::string const& name)
{
    scoped_lock lock(m_functionsMutex);
    auto func = m_functionList.find(name);
    if (func == m_functionList.end())
        throw std::runtime_error("No function found: " + name);

    return *func->second;
}

void VM::startClient(std::string const& clientName)
{
    auto& client = m_clients[clientName];
    // TODO: In Thread starten mit Knoten aus Grammatik
    client->thread = std::thread([this, client]{
        myClient = client;
        Context context(*this);
        // TODO: Client-Knoten ausführen
        //threadNode->second->execute(&context);
    });
}

Client& VM::getCurrentClient()
{
    return *myClient;
}


