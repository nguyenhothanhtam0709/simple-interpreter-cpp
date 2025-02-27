#include "ast.hpp"
#include "ast_node.hpp"

AbstractSyntaxTree::AbstractSyntaxTree(ProgramNode *root) : root_{root} {}
AbstractSyntaxTree::~AbstractSyntaxTree()
{
    // TODO: Implementing a mechanism to destroy all ast node
}

ProgramNode *AbstractSyntaxTree::get_root() { return root_; }