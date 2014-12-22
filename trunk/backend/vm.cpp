#include "vm.hpp"
#include "../frontend/nodes.hpp"
#include <iostream>

void VM::startThread(std::string const& name, std::string const& id)
{
    std::thread newThread;


}


void VM::registerThreads(ThreadListNode const* threadList)
{
    for(auto& threadNode:threadList->getThreads())
    {
        m_threadNodes[threadNode->getName()] = threadNode.get();
        std::cout << threadNode->getName() << " = Name\n";
    }
}
