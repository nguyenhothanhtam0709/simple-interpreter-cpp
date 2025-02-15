#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <token.hpp>

#define __THROW_PARSING_ERROR \
    throw std::runtime_error("Error parsing input");

constexpr char NULL_CHAR = '\0';
constexpr char WHITESPACE_CHAR = ' ';
constexpr char PLUS_CHAR = '+';
constexpr char MINUS_CHAR = '-';

class Interpreter
{
private:
    /// @brief an index to this->text
    int _pos = 0;

    /// @brief actual code
    const std::string _text;

    char _current_char;

    Token *_current_token = nullptr;

    void _error() const;

    /// @brief Advance the 'pos' pointer and set the 'current_char' variable.
    void _advance() noexcept;

    void _skip_whitespace() noexcept;

    /// @brief Return a (multidigit) integer string consumed from the input.
    std::string _integer() noexcept;

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