#include "interpreter.hpp"

#include "frontend/fcl.parser.hh"

#include "backend/object-functions.hpp"
#include "backend/client-functions.hpp"
#include "backend/thread-functions.hpp"
#include "backend/io-functions.hpp"
#include "backend/fire-functions.hpp"

extern std::FILE* yyin;

Interpreter::Interpreter()
    : m_vm()
    , m_rootNode()
{
}

Interpreter::~Interpreter()
{
    try
    {
        m_vm.shutdown();
    }
    catch (std::exception const& ex)
    {
        std::cerr << "Error while shutting down VM:\n"
            << ex.what() << std::endl;
    }
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
    m_vm.registerClients(m_rootNode->getClients().get());
    registerFunctions();
}

void Interpreter::executeProgram()
{
    Context context(m_vm);
    m_rootNode->execute(&context);
}

void Interpreter::registerFunctions()
{
    // Object
    registerFunction<GetType>();
    registerFunction<IsNull>();

    // Client
    registerFunction<StartClient>();
    registerFunction<SetClientId>();
    registerFunction<SetPosition>();

    // Thread
    registerFunction<StartThread>();
    registerFunction<JoinThread>();
    registerFunction<WaitThread>();

    // I/O
    registerFunction<WriteLine>();

    // Fire
    registerFunction<StartMission>();
    registerFunction<LoadPictures>();
    registerFunction<LoadPositions>();
    registerFunction<SendPicture>();
    registerFunction<SendPosition>();
    registerFunction<SendMessage>();
}
