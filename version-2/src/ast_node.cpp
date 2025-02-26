#include "ast_node.hpp"
#include <vector>
#include <string>
#include "token.hpp"

AstNode::AstNode(AstNodeType type) : type_{type} {}
AstNodeType AstNode::get_type() const noexcept { return type_; }

ProgramNode::ProgramNode(const std::string &name, BlockNode *block)
    : AstNode{AstNodeType::PROGRAM}, name_{name}, block_{block} {}
const std::string &ProgramNode::get_name() const noexcept { return name_; }
BlockNode *ProgramNode::get_block_node() const noexcept { return block_; }

BlockNode::BlockNode(std::vector<VarDeclNode *> declarations, CompoundStatementNode *compound_statement)
    : AstNode{AstNodeType::BLOCK}, declarations_{declarations}, compound_statement_{compound_statement} {}
std::vector<VarDeclNode *> BlockNode::get_declaration_nodes() const noexcept { return declarations_; }
CompoundStatementNode *BlockNode::get_compound_statement_node() const noexcept { return compound_statement_; }

VarDeclNode::VarDeclNode(VariableNode *var_node, TypeNode *type_node)
    : AstNode{AstNodeType::VARIABLE_DECLARATION}, var_{var_node}, type_{type_node} {}
VariableNode *VarDeclNode::get_var_node() const noexcept { return var_; }
TypeNode *VarDeclNode::get_type_node() const noexcept { return type_; }

CompoundStatementNode::CompoundStatementNode(std::vector<AstNode *> statement_list)
    : AstNode{AstNodeType::COMPOUND_STATEMENT}, statement_list_{statement_list} {}
std::vector<AstNode *> CompoundStatementNode::get_statement_list() const noexcept { return statement_list_; }

AssignmentStatementNode::AssignmentStatementNode(VariableNode *lhs, AstNode *rhs)
    : AstNode{AstNodeType::ASSIGNMENT_STATEMENT}, lhs_{lhs}, rhs_{rhs} {}
VariableNode *AssignmentStatementNode::get_lhs() const noexcept { return lhs_; }
AstNode *AssignmentStatementNode::get_rhs() const noexcept { return rhs_; }

VariableNode::VariableNode(const std::string &name) : AstNode{AstNodeType::VARIABLE}, name_{name} {}
const std::string &VariableNode::get_name() const noexcept { return name_; }

TypeNode::TypeNode(Token *token) : AstNode{AstNodeType::TYPE}, token_{token} {}
Token *TypeNode::get_token() const noexcept { return token_; }

NoOperationNode::NoOperationNode() : AstNode{AstNodeType::NO_OPERATION} {}