#include "interpreter.hpp"

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: fcl {filename}" << std::endl;
        return -1;
    }

    try
    {
        std::string filename = argv[1];
        Interpreter interpreter;
        interpreter.fire(filename);
        return 0;
    }
    catch (std::exception const& ex)
    {
        std::cerr << "An error occurred while interpreting the FCL program:\n"
            << ex.what() << std::endl;
        return -1;
    }
}
