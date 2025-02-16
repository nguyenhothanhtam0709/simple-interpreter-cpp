#include <cstdlib>
#include <iostream>
#include <string>
#include "interpreter.hpp"

int main()
{
    while (true)
    {
        std::string text;

        std::cout << "calc> ";
        std::getline(std::cin, text);

        Lexer *lexer = new Lexer(text);
        Interpreter *interpreter = new Interpreter(lexer);
        std::cout << interpreter->expr() << '\n';

        delete interpreter;
        delete lexer;
    }

    return EXIT_SUCCESS;
}