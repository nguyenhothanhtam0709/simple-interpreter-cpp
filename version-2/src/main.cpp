#include <cstdlib>
#include <iostream>
#include "interpreter/token.hpp"

int main()
{
    Token token(TokenType::INTEGER);

    std::cout << token << '\n';

    return EXIT_SUCCESS;
}