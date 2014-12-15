#ifndef VM_HPP_INCLUDED
#define VM_HPP_INCLUDED
#include <string>


class VM
{
public:
    void startThread(std::string name, std::string id);
    void joinThread(std::string id);
};

#endif // VM_HPP_INCLUDED
