#include <stdexcept>
#include <cctype>
#include "parser.hpp"
#include "ast.hpp"
#include "lexer.hpp"
#include "token.hpp"
#include "utils.hpp"

Parser::Parser(Lexer *lexer) : _lexer(lexer)
{
    _current_token = _lexer->get_next_token();
}

Parser::~Parser()
{
    delete _current_token;
}

void Parser::_error() const
{
    __THROW_PARSING_ERROR
}

void Parser::_eat(TokenType token_type)
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

ASTNode *Parser::_factor()
{
    Token *token = _current_token;
    if (token->getType() == TokenType::PLUS)
    {
        _eat(TokenType::PLUS);
        return new UnaryOpNode(token, _factor());
    }
    else if (token->getType() == TokenType::MINUS)
    {
        _eat(TokenType::MINUS);
        return new UnaryOpNode(token, _factor());
    }
    else if (token->getType() == TokenType::INTEGER)
    {
        _eat(TokenType::INTEGER);
        return new NumNode(token);
    }
    else if (token->getType() == TokenType::LPAREN)
    {
        _eat(TokenType::LPAREN);
        delete token; // delete LPAREN token pointer
        ASTNode *node = _expr();
        token = _current_token;
        _eat(TokenType::RPAREN);
        delete token; // delete RPAREN token pointer
        return node;
    }

    __THROW_PARSING_ERROR
}

ASTNode *Parser::_term()
{
    ASTNode *node = _factor();
    while (_current_token != nullptr &&
           (_current_token->getType() == TokenType::MUL || _current_token->getType() == TokenType::DIV))
    {
        Token *token = _current_token;
        if (token->getType() == TokenType::MUL)
        {
            _eat(TokenType::MUL);
        }
        else if (token->getType() == TokenType::DIV)
        {
            _eat(TokenType::DIV);
        }

        node = new BinOpNode(token, node, _factor());
    }

    return node;
}

ASTNode *Parser::_expr()
{
    ASTNode *node = _term();

    while (_current_token != nullptr &&
           (_current_token->getType() == TokenType::PLUS ||
            _current_token->getType() == TokenType::MINUS))
    {
        Token *token = _current_token;
        if (token->getType() == TokenType::PLUS)
        {
            _eat(TokenType::PLUS);
        }
        else if (token->getType() == TokenType::MINUS)
        {
            _eat(TokenType::MINUS);
        }

        node = new BinOpNode(token, node, _term());
    }

    return node;
}

AST *Parser::parse() noexcept
{
    ASTNode *root_node = _expr();
    return new AST(root_node);
}