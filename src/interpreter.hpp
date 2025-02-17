#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include "token.hpp"
#include "lexer.hpp"
#include "utils.hpp"

class Interpreter
{
private:
    Token *_current_token = nullptr;

    Lexer *_lexer;

    void _error() const;

    void _eat(TokenType token_type);

    /// @brief Return an INTEGER token value.
    std::string _factor();

    std::string _term();

public:
    Interpreter(Lexer *lexer);
    ~Interpreter();

    /// @brief expr -> INTEGER PLUS INTEGER
    int expr();
};

#endif