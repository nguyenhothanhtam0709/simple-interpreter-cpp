#include <cstdlib>
#include <iostream>
#include "token.hpp"
#include "lexer.hpp"

int main()
{
    Lexer *lexer = new Lexer("PROGRAM Part10AST; \
VAR \
   a, b : INTEGER; \
   y    : REAL; \
 \
BEGIN {Part10AST} \
   a := 2; \
   b := 10 * a + 10 * a DIV 4; \
   y := 20 / 7 + 3.14; \
END.  {Part10AST}");

    Token *token = lexer->get_next_token();
    while (token->get_type() != TokenType::END_OF_FILE)
    {
        switch (token->get_type())
        {
        case TokenType::INTEGER_NUMBER:
            std::cout << *(static_cast<IntNumToken *>(token)) << '\n';
            break;
        case TokenType::REAL_NUMBER:
            std::cout << *(static_cast<RealNumToken *>(token)) << '\n';
            break;
        case TokenType::ID:
            std::cout << *(static_cast<IdToken *>(token)) << '\n';
            break;
        default:
            std::cout << *token << '\n';
            break;
        }

        delete token;
        token = lexer->get_next_token();
    }

    delete token;
    delete lexer;

    return EXIT_SUCCESS;
}