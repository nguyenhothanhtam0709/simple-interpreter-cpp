#include <iostream>
#include <stdexcept>
#include <cctype>
#include <string>
#include "interpreter.hpp"

Interpreter::Interpreter(const std::string &text) : _text{text}, _current_char{_text[_pos]} {}

Interpreter::~Interpreter()
{
    delete _current_token;
}

void Interpreter::_error() const
{
    __THROW_PARSING_ERROR
}

// MARK: Lexer code
// Below codes are lexer code

void Interpreter::_advance() noexcept
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

void Interpreter::_skip_whitespace() noexcept
{
    while (_current_char != NULL_CHAR && _current_char == WHITESPACE_CHAR)
    {
        _advance();
    }
}

std::string Interpreter::_integer() noexcept
{
    std::string result = "";
    while (_current_char != NULL_CHAR && std::isdigit(_current_char))
    {
        result.push_back(_current_char);
        _advance();
    }

    return result;
}

Token *Interpreter::_get_next_token()
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

        __THROW_PARSING_ERROR
    }

    return new Token(TokenType::END_OF_FILE, NULL_CHAR);
}

// MARK: Parser code
// Below codes are parser code

void Interpreter::_eat(TokenType token_type)
{
    if (_current_token != nullptr && _current_token->getType() == token_type)
    {
        _current_token = _get_next_token();
    }
    else
    {
        __THROW_PARSING_ERROR
    }
}

std::string Interpreter::_term()
{
    Token *token = _current_token;
    _eat(TokenType::INTEGER);
    return token->getValue();
}

int Interpreter::expr()
{
    Token *first_token = _get_next_token();
    _current_token = first_token;

    int result = std::stoi(_term());
    delete first_token;
    first_token = nullptr;

    while (_current_token != nullptr && (_current_token->getType() == TokenType::PLUS || _current_token->getType() == TokenType::MINUS))
    {
        Token *token = _current_token;
        if (token->getType() == TokenType::PLUS)
        {
            _eat(TokenType::PLUS);
            result += std::stoi(_term());
        }
        else if (token->getType() == TokenType::MINUS)
        {
            _eat(TokenType::MINUS);
            result -= std::stoi(_term());
        }

        delete token;
    }

    return result;
}