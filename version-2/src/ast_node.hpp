#ifndef AST_NODE_HPP
#define AST_NODE_HPP

#include <string>
#include <vector>
#include "token.hpp"

enum class AstNodeType : unsigned char
{
    PROGRAM,
    BLOCK,
    COMPOUND_STATEMENT,
    VARIABLE_DECLARATION,
    ASSIGNMENT_STATEMENT,
    BINARY_OPERATOR,
    UNARY_OPERATOR,
    VARIABLE,
    TYPE,
    INT_NUM,
    REAL_NUM,
    /// @brief Present an empty statement
    NO_OPERATION
};

/// @brief Base AST node
class AstNode
{
public:
    explicit AstNode(AstNodeType type);
    virtual ~AstNode();

    AstNodeType get_type() const noexcept;

protected:
    AstNodeType type_;
};

/// @brief AST node containing a token
template <typename TToken = Token>
class TokenHolderNode : public AstNode
{
public:
    TokenHolderNode(AstNodeType type, TToken *token);
    virtual ~TokenHolderNode();

    /// @brief Get token belong to this node
    TToken *get_token() const noexcept;

protected:
    TToken *token_;
};

class VariableNode : public AstNode
{
public:
    VariableNode(const std::string &name);
    VariableNode(std::string &&name);

    /// @brief Get variable name
    const std::string &get_name() const noexcept;

protected:
    /// @brief var name
    std::string name_;
};

class TypeNode : public AstNode
{
public:
    TypeNode(Token *token);
    ~TypeNode();

    /// @brief Get token belong to this node
    Token *get_token() const noexcept;

protected:
    /// @brief token containing type
    Token *token_;
};

class CompoundStatementNode : public AstNode
{
public:
    explicit CompoundStatementNode(std::vector<AstNode *> &&statement_list);

    std::vector<AstNode *> get_statement_list() const noexcept;

protected:
    std::vector<AstNode *> statement_list_;
};

class VarDeclNode : public AstNode
{
public:
    VarDeclNode(VariableNode *var_node, TypeNode *type_node);

    /// @brief Get variable node
    VariableNode *get_var_node() const noexcept;
    /// @brief Get type node
    TypeNode *get_type_node() const noexcept;

protected:
    /// @brief variable node
    VariableNode *var_;
    /// @brief type node
    TypeNode *type_;
};

class BlockNode : public AstNode
{
public:
    BlockNode(std::vector<VarDeclNode *> &&declarations, CompoundStatementNode *compound_statement);

    std::vector<VarDeclNode *> get_declaration_nodes() const noexcept;
    CompoundStatementNode *get_compound_statement_node() const noexcept;

private:
    std::vector<VarDeclNode *> declarations_;
    CompoundStatementNode *compound_statement_;
};

class ProgramNode : public AstNode
{
public:
    ProgramNode(const std::string &name, BlockNode *block);
    ProgramNode(std::string &&name, BlockNode *block);

    /// @brief Get program name
    const std::string &get_name() const noexcept;
    /// @brief Get block node
    BlockNode *get_block_node() const noexcept;

private:
    std::string name_;
    BlockNode *block_;
};

class AssignmentStatementNode : public AstNode
{
public:
    AssignmentStatementNode(VariableNode *lhs, AstNode *rhs);

    VariableNode *get_lhs() const noexcept;
    AstNode *get_rhs() const noexcept;

private:
    VariableNode *lhs_;
    AstNode *rhs_;
};

class NoOperationNode : public AstNode
{
public:
    NoOperationNode();
};

class BinaryOperatorNode : public AstNode
{
    BinaryOperatorNode(Token *token, AstNode *lhs, AstNode *rhs);
    ~BinaryOperatorNode();

    /// @brief Get token belong to this node
    Token *get_token() const noexcept;
    AstNode *get_lhs() const noexcept;
    AstNode *get_rhs() const noexcept;

protected:
    /// @brief token containing operator
    Token *token_;
    AstNode *lhs_;
    AstNode *rhs_;
};

class UnaryOperatorNode : public AstNode
{
    UnaryOperatorNode(Token *token, AstNode *rhs);
    ~UnaryOperatorNode();

    /// @brief Get token belong to this node
    Token *get_token() const noexcept;
    AstNode *get_rhs() const noexcept;

protected:
    /// @brief token containing operator
    Token *token_;
    AstNode *rhs_;
};

class IntNumNode : public AstNode
{
public:
    IntNumNode(IntNumToken *token);
    ~IntNumNode();

    /// @brief Get token belong to this node
    IntNumToken *get_token() const noexcept;

protected:
    /// @brief token containing integer number
    IntNumToken *token_;
};

class RealNumNode : public AstNode
{
public:
    RealNumNode(RealNumToken *token);
    ~RealNumNode();

    /// @brief Get token belong to this node
    RealNumToken *get_token() const noexcept;

protected:
    /// @brief token containing real number
    RealNumToken *token_;
};

#endif