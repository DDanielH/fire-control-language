#include "interpreter.hpp"

#include "frontend/fcl.parser.hh"

#include "backend/client-functions.hpp"
#include "backend/io-functions.hpp"

extern std::FILE* yyin;

Interpreter::Interpreter()
    : m_vm()
    , m_rootNode()
{
}

Interpreter::~Interpreter()
{
    m_vm.joinAllThreads();
}

void Interpreter::fire(std::string const& filename)
{
    parseFile(filename);
    bootVM();
    executeProgram();
}

void Interpreter::parseFile(std::string const& filename)
{
    yyin = fopen(filename.c_str(), "r");
    if (yyin == NULL)
        throw std::runtime_error("Could not open file: " + filename);

    int parseResult = yyparse(&m_rootNode);
    fclose(yyin);
    if (parseResult != 0)
        throw std::runtime_error("Parse error: " + std::to_string(parseResult));
}

void Interpreter::bootVM()
{
    m_vm.registerThreads(m_rootNode->getThreads().get());
    registerFunctions();
}

void Interpreter::executeProgram()
{
    Context context(m_vm);
    m_rootNode->execute(&context);
}

void Interpreter::registerFunctions()
{
    m_vm.registerFunction(std::make_shared<CountFunction>());
    m_vm.registerFunction(std::make_shared<StartThread>());
    m_vm.registerFunction(std::make_shared<JoinThread>());

    m_vm.registerFunction(std::make_shared<GetType>());
    m_vm.registerFunction(std::make_shared<SendPosition>());
    m_vm.registerFunction(std::make_shared<SendPicture>());

    m_vm.registerFunction(std::make_shared<StartClient>());
    m_vm.registerFunction(std::make_shared<SetClientId>());
    m_vm.registerFunction(std::make_shared<SetPosition>());

    m_vm.registerFunction(std::make_shared<WriteLine>());

    m_vm.registerFunction(std::make_shared<LoadPicture>());
    m_vm.registerFunction(std::make_shared<LoadPosition>());
}
