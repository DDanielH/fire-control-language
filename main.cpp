#include "interpreter.hpp"

#include <iostream>

int main()
{
    const std::string TEST_FILE = "./test/test.fcl";

    try
    {
        Interpreter interpreter;
        interpreter.fire(TEST_FILE);
        return 0;
    }
    catch (std::exception const& ex)
    {
        std::cerr << "An error occurred while interpreting the FCL program:\n"
            << ex.what() << std::endl;
        return -1;
    }
}
