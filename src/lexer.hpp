#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include "token.hpp"

class Lexer
{
private:
    /// @brief an index to this->text
    int _pos = 0;

    /// @brief actual code
    const std::string _text;

    char _current_char;

    void _error() const;

    /// @brief Advance the 'pos' pointer and set the 'current_char' variable.
    void _advance() noexcept;

    void _skip_whitespace() noexcept;

    /// @brief Return a (multidigit) integer string consumed from the input.
    std::string _integer() noexcept;

public:
    Lexer(const std::string &text);

    /// @brief Lexical analyzer (also known as scanner or tokenizer)
    ///
    /// This method is responsible for breaking a sentence
    /// apart into tokens. One token at a time.
    Token *get_next_token();
};

#endif