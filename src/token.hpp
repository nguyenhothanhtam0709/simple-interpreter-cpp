#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

/// @brief Token types
enum class TokenType
{
    INTEGER,

    PLUS,
    MINUS,

    /// @brief EOF (end-of-file) token is used to indicate that
    /// there is no more input left for lexical analysis
    END_OF_FILE
};

class Token
{
private:
    const TokenType _type;
    const std::string _value;

public:
    Token(TokenType type);
    Token(TokenType type, const char value);
    Token(TokenType type, const std::string &value);

    TokenType getType() const noexcept;
    const std::string &getValue() const noexcept;
};

#endif