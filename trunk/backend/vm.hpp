#ifndef VM_HPP_INCLUDED
#define VM_HPP_INCLUDED

#include <string>
#include <thread>
#include <map>
#include <memory>
#include <mutex>

class ThreadListNode;
class ThreadNode;
class Function;


class VM
{
private:
    std::map<std::string, std::shared_ptr<std::thread>> m_runningThreads;
    std::map<std::string, ThreadNode const*> m_threadNodes;
    std::map<std::string, std::shared_ptr<Function>> m_functionList;
    std::map<std::string, std::shared_ptr<Client>> m_clients;
    std::mutex m_runningThreadMutex;
    std::mutex m_functionsMutex;
public:
    void startThread(std::string const& name, std::string const& id);
    void joinThread(std::string const& id);
    void registerThreads(ThreadListNode const* threadList);
    void joinAllThreads();

    void registerFunction(std::shared_ptr<Function> const& function);
    Function const& getFunctionByName(std::string const& name);

    void startClient(std::string const& clientName);
};


#endif // VM_HPP_INCLUDED
