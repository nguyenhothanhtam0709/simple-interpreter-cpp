#ifndef PARSER_HPP
#define PARSER_HPP

#include "ast.hpp"
#include "lexer.hpp"

class Parser
{
private:
    Token *_current_token = nullptr;

    Lexer *_lexer;

    void _error() const;

    void _eat(TokenType token_type);

    ASTNode *_factor();

    ASTNode *_term();

    ASTNode *_expr();

public:
    Parser(Lexer *lexer);
    ~Parser();

    AST *parse() noexcept;
};

#endif