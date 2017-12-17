#include <iostream>
#include "compiler.h"

static void usage(char **argv)
{
    std::cout << argv[0] << " <file.c>" << std::endl;
    exit(1);
}

int main(int argc, char **argv) 
{
    if (argc != 2)
        usage(argv);

    Compiler c(argv[1]);
    
    if (!c.compile())
    {
        std::cout << "Error compiling " << std::string(argv[1]) << std::endl;
        exit(1);
    }

    std::cout << "Compilation sucessfull" << std::endl;

    return 0;
}

