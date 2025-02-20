#include <queue>
#include <stdexcept>
#include "ast.hpp"

// MARK: Base AST node

ASTNode::ASTNode(Token *token) : _token(token) {}

ASTNode::~ASTNode()
{
    delete _token;
}

Token *ASTNode::getToken() const noexcept
{
    return _token;
}

// MARK: Number node

ASTNodeType NumNode::getType() const noexcept
{
    return _type;
}

// MARK: Binary node

BinOpNode::BinOpNode(Token *token, ASTNode *left_child, ASTNode *right_child)
    : ASTNode(token), _left_child(left_child), _right_child(right_child) {}

ASTNodeType BinOpNode::getType() const noexcept
{
    return _type;
}

ASTNode *BinOpNode::getLeftChild() const noexcept
{
    return _left_child;
}

ASTNode *BinOpNode::getRightChild() const noexcept
{
    return _right_child;
}

// MARK: Unary node

UnaryOpNode::UnaryOpNode(Token *token, ASTNode *child) : ASTNode(token), _child(child) {}

ASTNodeType UnaryOpNode::getType() const noexcept
{
    return _type;
}

ASTNode *UnaryOpNode::getChild() const noexcept
{
    return _child;
}

// MARK: Abstract syntax tree

AST::AST(ASTNode *root) : _root(root) {}

AST::~AST()
{
    if (_root == nullptr)
    {
        return;
    }

    std::queue<ASTNode *> nodes;
    nodes.emplace(_root);
    while (!nodes.empty())
    {
        ASTNode *current_node = nodes.front();
        nodes.pop();

        switch (current_node->getType())
        {
        case ASTNodeType::NUMBER:
        {
            break;
        }
        case ASTNodeType::UNARY_OPERATOR:
        {
            UnaryOpNode *unary_op_node = dynamic_cast<UnaryOpNode *>(current_node);
            nodes.emplace(unary_op_node->getChild());
            break;
        }
        case ASTNodeType::BINARY_OPERATOR:
        {
            BinOpNode *bin_op_node = dynamic_cast<BinOpNode *>(current_node);
            nodes.emplace(bin_op_node->getLeftChild());
            nodes.emplace(bin_op_node->getRightChild());
            break;
        }
        default:
            throw std::runtime_error("Unknow ast node type");
        }
        delete current_node;
    }
}

ASTNode *AST::getRoot() const noexcept
{
    return _root;
}