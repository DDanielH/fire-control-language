#include "frontend/nodes.hpp"
#include "frontend/fcl.parser.hh"

#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

extern std::FILE* yyin;

int main()
{
    const char* const TEST_FILE = "./test/calc.fcl";
    yyin = fopen(TEST_FILE, "r");
    if (yyin == NULL)
    {
        std::cerr << "Could not open file: " << TEST_FILE << std::endl;
        return -1;
    }

    std::unique_ptr<ExprNode> result;
    int parseResult = yyparse(&result);
    fclose(yyin);
    if (parseResult != 0)
    {
        std::cout << "Parse error: " << parseResult << std::endl;
        return -1;
    }

    std::cout << "Result: " << result->calculate() << std::endl;
    std::cout << "Polish: " << result->toReversePolishNotation() << std::endl;
    return 0;
}
