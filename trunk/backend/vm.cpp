#include "vm.hpp"
#include "../frontend/nodes.hpp"
#include "context.hpp"
#include <iostream>

void VM::startThread(std::string const& name, std::string const& id)
{
    auto threadNode = m_threadNodes.find(name);
    if(threadNode == m_threadNodes.end())
        throw std::runtime_error("Thread not found: "+ name);

    auto runnningThread = m_runningThreads.find(id);
    if(runnningThread != m_runningThreads.end())
        throw std::runtime_error("Thread with id already started: "+ id);

    m_runningThreads[id] = std::thread([threadNode]{
        Context context;
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

void VM::joinAllThreads()
{
    for (auto& thread : m_runningThreads)
    {
        thread.second.join();
    }
}
