#ifndef PARSER_HPP
#define PARSER_HPP

#include "parser.hpp"
#include "lexer.hpp"
#include "token.hpp"
#include "ast.hpp"

/// @brief A simple recursive-descent parser
class Parser
{
public:
    explicit Parser(Lexer *lexer);
    ~Parser();

    /// @brief Create AST from source code
    AST *parse();

protected:
    Lexer *lexer_;
    Token *current_token_ = nullptr;
};

#endif