#include "token.hpp"
#include <ostream>
#include <string>
#include <unordered_map>

Token::Token(TokenType type) : type_(type) {}
Token::Token(const Token &token) : type_(token.get_type()) {}

TokenType Token::get_type() const noexcept
{
    return type_;
}

std::ostream &operator<<(std::ostream &out_stream, const Token &token)
{
    return out_stream << "Token: " << map_token_type_to_string(token.get_type());
}
Token &Token::operator=(const Token &rhs)
{
    if (this != &rhs)
    {
        type_ = rhs.get_type();
    }

    return *this;
}

IdToken::IdToken(const std::string &value) : Token(TokenType::ID), value_(value) {}
IdToken::IdToken(std::string &&value) : Token(TokenType::ID), value_(std::move(value)) {}

const std::string &IdToken::get_value() const noexcept
{
    return value_;
}
std::ostream &operator<<(std::ostream &out_stream, const IdToken &token)
{
    return out_stream << "Token: " << map_token_type_to_string(token.get_type()) << "(" << token.get_value() << ")";
}

IntNumToken::IntNumToken(int value) : Token(TokenType::INTEGER_NUMBER), value_{value} {}
int IntNumToken::get_value() const noexcept { return value_; }
std::ostream &operator<<(std::ostream &out_stream, const IntNumToken &token)
{
    return out_stream << "Token: " << map_token_type_to_string(token.get_type()) << "(" << token.get_value() << ")";
}

RealNumToken::RealNumToken(float value) : Token(TokenType::REAL_NUMBER), value_{value} {}
float RealNumToken::get_value() const noexcept { return value_; }
std::ostream &operator<<(std::ostream &out_stream, const RealNumToken &token)
{
    return out_stream << "Token: " << map_token_type_to_string(token.get_type()) << "(" << token.get_value() << ")";
}

/// @brief Mapping TokenType to string
/// @warning This function is not thread-safe since the std::unordered_map is not thread-safe.
const std::string &map_token_type_to_string(const TokenType &token_type)
{
    static const std::unordered_map<TokenType, const std::string> kTokenStrMap = {
        {TokenType::BEGIN, "BEGIN"},
        {TokenType::END, "END"},
        {TokenType::PROGRAM, "PROGRAM"},
        {TokenType::VAR, "VAR"},
        {TokenType::INTEGER, "INTEGER"},
        {TokenType::REAL, "REAL"},

        {TokenType::ASSIGN, "ASSIGN"},
        {TokenType::PLUS, "PLUS"},
        {TokenType::MINUS, "MINUS"},
        {TokenType::MUL, "MUL"},
        {TokenType::FLOAT_DIV, "FLOAT_DIV"},
        {TokenType::INTEGER_DIV, "INTEGER_DIV"},

        {TokenType::DOT, "DOT"},
        {TokenType::COLON, "COLON"},
        {TokenType::SEMI_COLON, "SEMI_COLON"},
        {TokenType::COMMA, "COMMA"},
        {TokenType::LPAREN, "LPAREN"},
        {TokenType::RPAREN, "RPAREN"},

        {TokenType::ID, "ID"},
        {TokenType::INTEGER_NUMBER, "INTEGER_NUMBER"},
        {TokenType::REAL_NUMBER, "REAL_NUMBER"},

        {TokenType::END_OF_FILE, "END_OF_FILE"}};
    /// @note Persisting static string to prevent potential dangling reference error
    static const std::string kUnknownStr = "UNKNOWN TOKEN TYPE";

    auto it = kTokenStrMap.find(token_type);

    /// @note "UNKNOWN" is a temporary string literal, and returning it as const std::string& would cause a dangling reference
    // return (it != token_str_map.end()) ? it->second : "UNKNOWN";

    return (it != kTokenStrMap.end()) ? it->second : kUnknownStr;
}