#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include "token.hpp"

#define __THROW_TOKENIZING_ERROR \
    throw std::runtime_error("Error tokenizing input");

/// @brief Lexical analyzer (also known as scanner or tokenizer)
class Lexer
{
public:
    explicit Lexer(const std::string &code);
    explicit Lexer(std::string &&code);

    /// @brief This method is responsible for breaking a sentence
    /// apart into tokens. One token at a time.
    Token *get_next_token();

protected:
    /// @brief Program code to be tokenized
    std::string code_;
    /// @brief Current char
    char current_char_;
    /// @brief Position of current_char_ in code_
    int pos_ = 0;

    /// @brief Advance the 'pos' pointer and set the 'current_char' variable.
    void advance() noexcept;
    /// @brief Peeking into the 'code_' buffer without actually consuming the next character.
    char peek() const noexcept;
    /// @brief ignore whitespace
    void skip_whitespace() noexcept;
    /// @brief ignore comment
    void skip_comment() noexcept;
    /// @brief Handle identifiers and reserved keywords
    Token* id() noexcept;
    /// @brief Return a (multidigit) integer or float consumed from the input.
    Token* number() noexcept;
};

#endif