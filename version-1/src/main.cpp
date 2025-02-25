#include <cstdlib>
#include <iostream>
#include <string>
#include "ast.hpp"
#include "parser.hpp"
#include "interpreter.hpp"

int main()
{
    while (true)
    {
        std::string text;

        std::cout << "calc> ";
        std::getline(std::cin, text);

        Lexer *lexer = new Lexer(text);
        Parser *parser = new Parser(lexer);
        Interpreter *interpreter = new Interpreter(parser);
        std::cout << interpreter->interpret() << '\n';

        delete interpreter;
        delete parser;
        delete lexer;
    }

    return EXIT_SUCCESS;
}