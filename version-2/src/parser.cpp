#include "parser.hpp"
#include "ast.hpp"
#include "ast_node.hpp"
#include "token.hpp"

Parser::Parser(Lexer *lexer) : lexer_{lexer}
{
    current_token_ = lexer_->get_next_token();
}
Parser::~Parser()
{
    // delete current_token_;
}

AbstractSyntaxTree *Parser::parse()
{
    ProgramNode *root_node = _program();
    AbstractSyntaxTree *ast = new AbstractSyntaxTree(root_node);
    return ast;
}

ProgramNode *Parser::_program()
{
    eat_and_ignore(TokenType::PROGRAM);

    Token *id_token = current_token_;
    eat(TokenType::ID);
    IdToken *casted_id_token = static_cast<IdToken *>(id_token);
    /// @note make copy to preventing use-after-free
    std::string program_name = casted_id_token->get_value();
    delete casted_id_token;

    eat_and_ignore(TokenType::SEMI_COLON);

    BlockNode *block_node = _block();

    eat_and_ignore(TokenType::DOT);

    ProgramNode *program_node = new ProgramNode(std::move(program_name), block_node);
    return program_node;
}

BlockNode *Parser::_block()
{
    return new BlockNode(_declarations(), _compound_statement());
}

std::vector<VarDeclNode *> Parser::_declarations()
{
    std::vector<VarDeclNode *> decl_list;
    if (current_token_->get_type() == TokenType::VAR)
    {
        eat_and_ignore(TokenType::VAR);
        while (current_token_->get_type() == TokenType::ID)
        {
            std::vector<VarDeclNode *> decls = _variable_declaration();
            decl_list.insert(decl_list.end(),
                             std::make_move_iterator(decls.begin()),
                             std::make_move_iterator(decls.end()));

            eat_and_ignore(TokenType::SEMI_COLON);
        }
    }

    /// @note The compiler applies Return Value Optimization (RVO), no extra move/copy
    return decl_list;
}

std::vector<VarDeclNode *> Parser::_variable_declaration()
{
    Token *id_token = current_token_;
    eat(TokenType::ID);
    /// @note make a copy to prevent potential Use-After-Free
    std::string id_node_name = std::string((static_cast<IdToken *>(id_token))->get_value());
    delete id_token;

    std::vector<VariableNode *> var_nodes = {new VariableNode(id_node_name)};
    while (current_token_->get_type() != TokenType::COLON)
    {
        eat_and_ignore(TokenType::COMMA);

        Token *id_token = current_token_;
        eat(TokenType::ID);
        /// @note make a copy to prevent potential Use-After-Free
        std::string id_node_name = std::string((static_cast<IdToken *>(id_token))->get_value());
        delete id_token;

        var_nodes.push_back(new VariableNode(id_node_name));
    }

    eat_and_ignore(TokenType::COLON);

    TypeNode *type_node = _type_spec();
    std::vector<VarDeclNode *> var_decl_nodes;
    for (auto &var_node : var_nodes)
    {
        var_decl_nodes.push_back(new VarDeclNode(var_node, new TypeNode(*type_node)));
    }
    delete type_node;

    /// @note The compiler applies Return Value Optimization (RVO), no extra move/copy
    return var_decl_nodes;
}

TypeNode *Parser::_type_spec()
{
    Token *type_token = current_token_;
    switch (type_token->get_type())
    {
    case TokenType::INTEGER:
        eat(TokenType::INTEGER);
        break;
    case TokenType::REAL:
        eat(TokenType::REAL);
        break;
    default:
        __THROW_PARSING_ERROR
    }

    return new TypeNode(type_token);
}

CompoundStatementNode *Parser::_compound_statement()
{
    eat_and_ignore(TokenType::BEGIN);
    CompoundStatementNode *node = new CompoundStatementNode(std::move(_statement_list()));
    eat_and_ignore(TokenType::END);
    return node;
}

std::vector<AstNode *> Parser::_statement_list()
{
    std::vector<AstNode *> statements = {_statement()};
    while (current_token_->get_type() == TokenType::SEMI_COLON)
    {
        eat_and_ignore(TokenType::SEMI_COLON);
        statements.push_back(_statement());
    }

    if (current_token_->get_type() == TokenType::ID)
    {
        __THROW_PARSING_ERROR
    }

    return statements;
}

AstNode *Parser::_statement()
{
    switch (current_token_->get_type())
    {
    case TokenType::BEGIN:
        return _compound_statement();
    case TokenType::ID:
        return _assignment_statement();
    default:
        return _empty();
    }
}

NoOperationNode *Parser::_empty()
{
    return new NoOperationNode();
}

void Parser::eat_and_ignore(const TokenType &token_type)
{
    Token *token = current_token_;
    eat(token_type);
    delete token;
}

void Parser::eat(const TokenType &token_type)
{
    if (current_token_ != nullptr && current_token_->get_type() == token_type)
    {
        current_token_ = lexer_->get_next_token();
        return;
    }

    __THROW_PARSING_ERROR
}