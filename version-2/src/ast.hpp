#ifndef AST_HPP
#define AST_HPP

#include "ast_node.hpp"

/// @brief Abstract syntax tree
class AbstractSyntaxTree
{
public:
    explicit AbstractSyntaxTree(ProgramNode *root);
    ~AbstractSyntaxTree();

    /// @brief Root node
    ProgramNode *get_root();

private:
    ProgramNode *root_;
};

#endif