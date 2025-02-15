#include <iostream>
#include <stdexcept>
#include <cctype>
#include <string>
#include "interpreter.hpp"

Interpreter::Interpreter(const std::string &text) : _text{text} {}

Interpreter::~Interpreter()
{
    delete _current_token;
}

void Interpreter::_error() const
{
    throw std::runtime_error("Error parsing input");
}

Token *Interpreter::_get_next_token()
{
    const int len_text = _text.length();

    if (_pos > len_text - 1)
    {
        return new Token(TokenType::END_OF_FILE, "");
    }

    char current_char = _text[_pos];
    if (std::isdigit(current_char))
    {
        _pos++;
        return new Token(TokenType::INTEGER, current_char);
    }
    if (current_char == '+')
    {
        _pos++;
        return new Token(TokenType::PLUS, '+');
    }

    throw std::runtime_error("Error parsing input");
}

void Interpreter::_eat(TokenType token_type)
{
    if (_current_token != nullptr && _current_token->getType() == token_type)
    {
        _current_token = _get_next_token();
    }
    else
    {
        throw std::runtime_error("Error parsing input");
    }
}

int Interpreter::expr()
{
    _current_token = _get_next_token();

    Token *left = _current_token;
    _eat(TokenType::INTEGER);

    Token *op = _current_token;
    _eat(TokenType::PLUS);

    Token *right = _current_token;
    _eat(TokenType::INTEGER);

    int result = std::stoi(left->getValue()) + std::stoi(right->getValue());

    delete left;
    delete op;
    delete right;

    return result;
}