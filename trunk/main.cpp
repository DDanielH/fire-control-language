#include "frontend/nodes.hpp"
#include "frontend/fcl.parser.hh"
#include "backend/function.hpp"

#include <iostream>
#include <string>
#include <cstdio>
#include "backend/vm.hpp"

using namespace std;

extern std::FILE* yyin;

int main()
{
    const char* const TEST_FILE = "./test/test.fcl";
    yyin = fopen(TEST_FILE, "r");
    if (yyin == NULL)
    {
        std::cerr << "Could not open file: " << TEST_FILE << std::endl;
        return -1;
    }

    std::unique_ptr<ProgramNode> result;
    int parseResult = yyparse(&result);
    fclose(yyin);
    ProgramNode* rootNode = result.get();
    if (parseResult != 0)
    {
        std::cout << "Parse error: " << parseResult << std::endl;
        return -1;
    }

    VM vmFire;
    vmFire.registerThreads(result->getThreads().get());
    vmFire.registerFunction(std::make_shared<CountFunction>());

    vmFire.startThread("willi","testtest");


    vmFire.joinAllThreads();
    std::cout << ":-)" << std::endl;

    return 0;
}
