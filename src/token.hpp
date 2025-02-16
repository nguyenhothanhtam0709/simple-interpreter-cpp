#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include "utils.hpp"

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