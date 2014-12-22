#include "vm.hpp"
#include "context.hpp"

#include "../frontend/nodes.hpp"

#include <iostream>

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
        std::cout << threadNode->getName() << " = Name\n";
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
}

Function const& VM::getFunctionByName(std::string const& name)
{
    scoped_lock lock(m_functionsMutex);
    auto func = m_functionList.find(name);
    if (func == m_functionList.end())
        throw std::runtime_error("No function found: " + name);

    return *func->second;
}
