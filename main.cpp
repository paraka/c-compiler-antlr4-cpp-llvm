#include <iostream>
#include <antlr4-runtime.h>
#include <CLexer.h>
#include <CParser.h>

using namespace antlr4;
using namespace antlrcpptest;

int main(void) 
{
    std::string line;
    std::ifstream sample("../samples/simple.c");

    if (sample.is_open()) 
    {
        ANTLRInputStream input(sample);
        CLexer lexer(&input);
        CommonTokenStream tokens(&lexer);

        tokens.fill();

        for (const auto &token : tokens.getTokens()) 
            std::cout << "TOKEN: " << token->toString() << std::endl;

        CParser parser(&tokens);
        tree::ParseTree *tree = parser.compilationUnit();
        std::cout << tree->toStringTree(&parser) << std::endl;
        sample.close();
    }

    return 0;
}

