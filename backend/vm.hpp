#ifndef VM_HPP_INCLUDED
#define VM_HPP_INCLUDED
#include <string>
#include <thread>
#include <map>
class ThreadListNode;
class ThreadNode;
class Function;


class VM
{
private:
    std::map<std::string,std::thread> m_runningThreads;
    std::map<std::string,ThreadNode const*> m_threadNodes;
    std::map<std::string,Function const*> m_functionList;
public:
    void startThread(std::string const& name, std::string const& id);
    void joinThread(std::string const& id);
    void registerThreads(ThreadListNode const* threadList);
    void joinAllThreads();

    Function getFunctionByName(std::string const& name);
};


#endif // VM_HPP_INCLUDED
