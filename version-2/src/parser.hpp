#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include "parser.hpp"
#include "lexer.hpp"
#include "token.hpp"
#include "ast.hpp"
#include "ast_node.hpp"

#define __THROW_PARSING_ERROR \
    throw std::runtime_error("Error parsing input");

/// @brief A simple recursive-descent parser
class Parser
{
public:
    explicit Parser(Lexer *lexer);
    ~Parser();

    /// @brief Create AST from source code
    AbstractSyntaxTree *parse();

private:
    Lexer *lexer_;
    Token *current_token_ = nullptr;

    /// @brief Handle program node
    /// @note ```ebnf
    /// program : PROGRAM variable SEMI block DOT
    /// ```
    ProgramNode *_program();

    /// @brief Handle block node
    /// @note ```ebnf
    /// block : declarations compound_statement
    /// ```
    BlockNode *_block();

    /// @brief Handle declarations
    /// @note ```ebnf
    /// declarations : VAR (variable_declaration SEMI)+
    ///              | empty
    /// ```
    std::vector<VarDeclNode *> _declarations();

    /// @brief Handle variable_declaration
    /// @note ```ebnf
    /// variable_declaration : ID (COMMA ID)* COLON type_spec
    /// ``
    std::vector<VarDeclNode *> _variable_declaration();

    /// @brief Handle type_spec
    /// @note ```ebnf
    /// type_spec : INTEGER
    ///           | REAL
    /// ```
    TypeNode *_type_spec();

    /// @brief Handle compound statement node
    /// @note ```ebnf
    /// compound_statement : BEGIN statement_list END
    /// ```
    CompoundStatementNode *_compound_statement();

    /// @brief Handle statement_list node
    /// @note ```ebnf
    /// statement_list : statement
    ///                | statement SEMI statement_list
    /// ```
    std::vector<AstNode *> _statement_list();

    /// @brief Handle statement node
    /// @note ```ebnf
    /// statement : compound_statement
    ///           | assignment_statement
    ///           | empty
    /// ```
    AstNode *_statement();

    /// @brief Handle assignment_statement node
    /// @note ```ebnf
    /// assignment_statement : variable ASSIGN expr
    /// ```
    AssignmentStatementNode *_assignment_statement();

    /// @brief Handle empty node
    /// @note ```ebnf
    /// empty : 
    /// ```
    NoOperationNode* _empty();

    /// @brief Eat the current token without adding to AST
    void eat_and_ignore(const TokenType &token_type);

    /// @brief compare the current token type with the passed token
    /// type and if they match then "eat" the current token
    /// and assign the next token to the self._current_token,
    /// otherwise raise and exception
    void eat(const TokenType &token_type);
};

#endif