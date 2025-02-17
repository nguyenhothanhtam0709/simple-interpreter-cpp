#include <iostream>
#include <stdexcept>
#include <cctype>
#include <string>
#include "interpreter.hpp"
#include "token.hpp"
#include "lexer.hpp"
#include "utils.hpp"

Interpreter::Interpreter(Lexer *lexer) : _lexer(lexer)
{
    _current_token = _lexer->get_next_token();
}

Interpreter::~Interpreter()
{
    delete _current_token;
}

void Interpreter::_error() const
{
    __THROW_PARSING_ERROR
}

void Interpreter::_eat(TokenType token_type)
{
    if (_current_token != nullptr && _current_token->getType() == token_type)
    {
        _current_token = _lexer->get_next_token();
    }
    else
    {
        __THROW_PARSING_ERROR
    }
}

std::string Interpreter::_factor()
{
    Token *token = _current_token;
    if (token->getType() == TokenType::INTEGER)
    {
        _eat(TokenType::INTEGER);
        std::string value = token->getValue();
        delete token;
        return value;
    }
    else if (token->getType() == TokenType::LPAREN)
    {
        _eat(TokenType::LPAREN);
        delete token; // delete LPAREN token pointer
        std::string result = expr();
        token = _current_token;
        _eat(TokenType::RPAREN);
        delete token; // delete RPAREN token pointer
        return result;
    }

    __THROW_PARSING_ERROR
}

std::string Interpreter::_term()
{
    int result = std::stoi(_factor());
    while (_current_token != nullptr &&
           (_current_token->getType() == TokenType::MUL || _current_token->getType() == TokenType::DIV))
    {
        Token *token = _current_token;
        if (token->getType() == TokenType::MUL)
        {
            _eat(TokenType::MUL);
            result *= std::stoi(_factor());
        }
        else if (token->getType() == TokenType::DIV)
        {
            _eat(TokenType::DIV);
            result /= std::stoi(_factor());
        }

        delete token;
    }

    return std::to_string(result);
}

std::string Interpreter::expr()
{
    int result = std::stoi(_term());

    while (_current_token != nullptr &&
           (_current_token->getType() == TokenType::PLUS ||
            _current_token->getType() == TokenType::MINUS))
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

    return std::to_string(result);
}