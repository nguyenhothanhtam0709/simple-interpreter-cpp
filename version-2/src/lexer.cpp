#include "lexer.hpp"
#include <string>
#include <unordered_map>
#include "token.hpp"

static const std::unordered_map<std::string, Token> kReversedKeywordTokenMap = {
    {"BEGIN", Token(TokenType::BEGIN)},
    {"END", Token(TokenType::END)},
    {"PROGRAM", Token(TokenType::PROGRAM)},
    {"VAR", Token(TokenType::VAR)},
    {"INTEGER", Token(TokenType::INTEGER)},
    {"REAL", Token(TokenType::REAL)}};

/// @note This constructor make a copy of code
Lexer::Lexer(const std::string &code) : code_{code}, current_char_{code_[pos_]} {}
/// @note This constructor make a move of code instead of copy
Lexer::Lexer(std::string &&code) : code_{std::move(code)}, current_char_{code_[pos_]} {}

void Lexer::advance() noexcept
{
    pos_++;
    current_char_ = (pos_ > code_.length() - 1) ? kNull : code_[pos_];
}

char Lexer::peek() const noexcept
{
    int peek_pos = pos_ + 1;
    return (peek_pos > code_.length() - 1) ? kNull : code_[peek_pos];
}

void Lexer::skip_whitespace() noexcept
{
    while (current_char_ != kNull && current_char_ == kWhitespace)
    {
        advance();
    }
}

void Lexer::skip_comment() noexcept
{
    while (current_char_ != kRightCurlyBrace)
    {
        advance();
    }

    /// @note ignore the closing curly brace, aka. '}'
    advance();
}

Token *Lexer::id() noexcept
{
    std::string result;
    while (current_char_ != kNull && std::isalnum(current_char_))
    {
        result += current_char_;
        advance();
    }

    auto it = kReversedKeywordTokenMap.find(result);
    return (it != kReversedKeywordTokenMap.end()) ? new Token(it->second) : new IdToken(result);
}

Token *Lexer::number() noexcept
{
    std::string result;
    while (current_char_ != kNull && std::isdigit(current_char_))
    {
        result += current_char_;
        advance();
    }

    if (current_char_ == kDot)
    {
        result += current_char_;
        advance();

        while (current_char_ != kNull && std::isdigit(current_char_))
        {
            result += current_char_;
            advance();
        }

        return new RealToken(std::stof(result));
    }

    return new IntToken(std::stoi(result));
}

Token *Lexer::get_next_token()
{
    while (current_char_ != kNull)
    {
        if (current_char_ == kWhitespace)
        {
            skip_whitespace();
            continue;
        }

        if (current_char_ == kLeftCurlyBrace)
        {
            skip_comment();
            continue;
        }

        if (std::isalpha(current_char_))
        {
            return id();
        }

        if (std::isdigit(current_char_))
        {
            return number();
        }

        if (current_char_ == kColon)
        {
            if (peek() == kEqualsSign)
            {
                advance(); // ":"
                advance(); // "="
                return new Token(TokenType::ASSIGN);
            }

            advance();
            return new Token(TokenType::COLON);
        }

        if (current_char_ == kSemiColon)
        {
            advance();
            return new Token(TokenType::SEMI_COLON);
        }

        if (current_char_ == kDot)
        {
            advance();
            return new Token(TokenType::DOT);
        }

        if (current_char_ == kPlus)
        {
            advance();
            return new Token(TokenType::PLUS);
        }

        if (current_char_ == kMinus)
        {
            advance();
            return new Token(TokenType::MINUS);
        }

        if (current_char_ == kMul)
        {
            advance();
            return new Token(TokenType::MUL);
        }

        if (current_char_ == kForwardSlash)
        {
            advance();
            return new Token(TokenType::FLOAT_DIV);
        }

        if (current_char_ == kLParen)
        {
            advance();
            return new Token(TokenType::LPAREN);
        }

        if (current_char_ == kRParen)
        {
            advance();
            return new Token(TokenType::RPAREN);
        }

        if (current_char_ == kComma)
        {
            advance();
            return new Token(TokenType::COMMA);
        }

        __THROW_PARSING_ERROR
    }

    return new Token(TokenType::END_OF_FILE);
}