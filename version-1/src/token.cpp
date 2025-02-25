#include <string>
#include "token.hpp"
#include "utils.hpp"

Token::Token(TokenType type) : Token(type, "") {}
Token::Token(TokenType type, const char value) : Token(type, std::string{value}) {}
Token::Token(TokenType type, const std::string &value) : _type{type}, _value{value} {}

TokenType Token::getType() const noexcept
{
    return _type;
}

const std::string &Token::getValue() const noexcept
{
    return _value;
}