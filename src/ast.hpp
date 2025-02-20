#ifndef AST_HPP
#define AST_HPP

#include "token.hpp"
#include "utils.hpp"

enum class ASTNodeType : unsigned char
{
    NUMBER,
    BINARY_OPERATOR,
    UNARY_OPERATOR
};

class ASTNode
{
private:
    Token *_token;

public:
    ASTNode(Token *token);
    virtual ~ASTNode();

    /// @brief Token of node
    Token *getToken() const noexcept;
    /// @brief Type of node
    virtual ASTNodeType getType() const noexcept = 0;
};

class NumNode : public ASTNode
{
private:
    const static ASTNodeType _type = ASTNodeType::NUMBER;

public:
    using ASTNode::ASTNode;

    /// @brief Type of node
    ASTNodeType getType() const noexcept override;
};

class BinOpNode : public ASTNode
{
private:
    const static ASTNodeType _type = ASTNodeType::BINARY_OPERATOR;

    ASTNode *_left_child;
    ASTNode *_right_child;

public:
    BinOpNode(Token *token, ASTNode *left_child, ASTNode *right_child);

    /// @brief Type of node
    ASTNodeType getType() const noexcept override;
    ASTNode *getLeftChild() const noexcept;
    ASTNode *getRightChild() const noexcept;
};

class UnaryOpNode : public ASTNode
{
private:
    const static ASTNodeType _type = ASTNodeType::UNARY_OPERATOR;

    ASTNode *_child;

public:
    UnaryOpNode(Token *token, ASTNode *child);

    /// @brief Type of node
    ASTNodeType getType() const noexcept override;
    ASTNode *getChild() const noexcept;
};

class AST
{
private:
    ASTNode *_root;

public:
    AST(ASTNode *root);
    ~AST();

    ASTNode *getRoot() const noexcept;
};

#endif