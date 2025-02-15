#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <token.hpp>

class Interpreter
{
private:
    /// @brief an index to this->text
    int _pos = 0;

    /// @brief actual code
    const std::string _text;

    Token *_current_token = nullptr;

    void _error() const;

    /// @brief Lexical analyzer (also known as scanner or tokenizer)
    ///
    /// This method is responsible for breaking a sentence
    /// apart into tokens. One token at a time.
    Token *_get_next_token();

    void _eat(TokenType token_type);

public:
    Interpreter(const std::string &text);
    ~Interpreter();

    /// @brief expr -> INTEGER PLUS INTEGER
    int expr();
};

#endif