#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "backend/vm.hpp"
#include "frontend/nodes.hpp"


class Interpreter
{
public:
    Interpreter();

    ~Interpreter();

    void fire(std::string const& filename);

private:
    void parseFile(std::string const& filename);
    void bootVM();
    void executeProgram();

    void registerFunctions();

private:
    VM m_vm;
    std::unique_ptr<ProgramNode> m_rootNode;
};

#endif // INTERPRETER_H
