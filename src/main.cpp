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
        std::cin >> text;

        Interpreter *interpreter = new Interpreter(text);
        std::cout << interpreter->expr() << '\n';

        delete interpreter;
    }

    return EXIT_SUCCESS;
}