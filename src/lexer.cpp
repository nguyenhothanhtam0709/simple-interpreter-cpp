#include <string>
#include <stdexcept>
#include <cctype>
#include "lexer.hpp"
#include "token.hpp"
#include "utils.hpp"

Lexer::Lexer(const std::string &text) : _text{text}, _current_char{_text[_pos]} {}

void Lexer::_error() const
{
    __THROW_PARSING_ERROR
}

void Lexer::_advance() noexcept
{
    _pos++;
    if (_pos > _text.length() - 1)
    {
        _current_char = NULL_CHAR;
    }
    else
    {
        _current_char = _text[_pos];
    }
}

void Lexer::_skip_whitespace() noexcept
{
    while (_current_char != NULL_CHAR && _current_char == WHITESPACE_CHAR)
    {
        _advance();
    }
}

std::string Lexer::_integer() noexcept
{
    std::string result = "";
    while (_current_char != NULL_CHAR && std::isdigit(_current_char))
    {
        result.push_back(_current_char);
        _advance();
    }

    return result;
}

Token *Lexer::get_next_token()
{
    while (_current_char != NULL_CHAR)
    {
        if (_current_char == WHITESPACE_CHAR)
        {
            _skip_whitespace();
            continue;
        }

        if (std::isdigit(_current_char))
        {
            return new Token(TokenType::INTEGER, _integer());
        }

        if (_current_char == PLUS_CHAR)
        {
            _advance();
            return new Token(TokenType::PLUS, PLUS_CHAR);
        }

        if (_current_char == MINUS_CHAR)
        {
            _advance();
            return new Token(TokenType::MINUS, MINUS_CHAR);
        }

        if (_current_char == MUL_CHAR)
        {
            _advance();
            return new Token(TokenType::MUL, MINUS_CHAR);
        }

        if (_current_char == DIV_CHAR)
        {
            _advance();
            return new Token(TokenType::DIV, DIV_CHAR);
        }

        __THROW_PARSING_ERROR
    }

    return new Token(TokenType::END_OF_FILE, NULL_CHAR);
}