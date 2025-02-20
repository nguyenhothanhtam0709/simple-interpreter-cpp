#include <stdexcept>
#include <cctype>
#include <string>
#include "interpreter.hpp"
#include "token.hpp"
#include "lexer.hpp"
#include "utils.hpp"

std::string ASTNodeVisitor::_visit(ASTNode *node)
{
    switch (node->getType())
    {
    case ASTNodeType::NUMBER:
    {
        NumNode *num_node = dynamic_cast<NumNode *>(node);
        return num_node->getToken()->getValue();
    }
    case ASTNodeType::UNARY_OPERATOR:
    {
        UnaryOpNode *unary_op_node = dynamic_cast<UnaryOpNode *>(node);
        Token *token = unary_op_node->getToken();
        if (token->getType() == TokenType::PLUS)
        {
            return _visit(unary_op_node->getChild());
        }
        else if (token->getType() == TokenType::MINUS)
        {
            return std::to_string(-std::stoi(_visit(unary_op_node->getChild())));
        }

        __THROW_INVALID_AST_NODE_ERROR
    }
    case ASTNodeType::BINARY_OPERATOR:
    {
        BinOpNode *bin_op_node = dynamic_cast<BinOpNode *>(node);
        switch (bin_op_node->getToken()->getType())
        {
        case TokenType::PLUS:
        {
            return std::to_string(
                std::stoi(_visit(bin_op_node->getLeftChild())) + std::stoi(_visit(bin_op_node->getRightChild())));
        }
        case TokenType::MINUS:
        {
            return std::to_string(
                std::stoi(_visit(bin_op_node->getLeftChild())) - std::stoi(_visit(bin_op_node->getRightChild())));
        }
        case TokenType::MUL:
        {
            return std::to_string(
                std::stoi(_visit(bin_op_node->getLeftChild())) * std::stoi(_visit(bin_op_node->getRightChild())));
        }
        case TokenType::DIV:
        {
            return std::to_string(
                std::stoi(_visit(bin_op_node->getLeftChild())) / std::stoi(_visit(bin_op_node->getRightChild())));
        }
        default:
            __THROW_INVALID_AST_NODE_ERROR
        }
    }
    default:
        __THROW_INVALID_AST_NODE_ERROR
    }
}

std::string ASTWalker::_walk(AST *ast)
{
    return _visit(ast->getRoot());
}

Interpreter::Interpreter(Parser *parser) : _parser(parser)
{
}

std::string Interpreter::interpret()
{
    AST *ast = _parser->parse();
    std::string result = _walk(ast);
    delete ast;
    return result;
}