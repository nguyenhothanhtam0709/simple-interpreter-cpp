#include "ast_node.hpp"
#include <vector>
#include <string>
#include "token.hpp"

AstNode::AstNode(AstNodeType type) : type_{type} {}
AstNode::~AstNode() {}
AstNodeType AstNode::get_type() const noexcept { return type_; }

VariableNode::VariableNode(const std::string &name) : AstNode{AstNodeType::VARIABLE}, name_{name} {}
VariableNode::VariableNode(std::string &&name) : AstNode{AstNodeType::VARIABLE}, name_{std::move(name)} {}
const std::string &VariableNode::get_name() const noexcept { return name_; }

// TypeNode::TypeNode(Token *token) : AstNode{AstNodeType::TYPE}, token_{token} {}
// TypeNode::TypeNode(const TypeNode &node)
//     : AstNode{AstNodeType::TYPE}, token_{new Token(*(node.get_token()))} {}
TypeNode::TypeNode(Token *token) : TokenHolderNode{AstNodeType::TYPE, token} {}
TypeNode::TypeNode(const TypeNode &node)
    : TokenHolderNode{AstNodeType::TYPE, new Token(*(node.get_token()))} {}
// TypeNode::~TypeNode() { delete token_; }
// Token *TypeNode::get_token() const noexcept { return token_; }

CompoundStatementNode::CompoundStatementNode(std::vector<AstNode *> &&statement_list)
    : AstNode{AstNodeType::COMPOUND_STATEMENT}, statement_list_{std::move(statement_list)} {}
std::vector<AstNode *> CompoundStatementNode::get_statement_list() const noexcept { return statement_list_; }

VarDeclNode::VarDeclNode(VariableNode *var_node, TypeNode *type_node)
    : AstNode{AstNodeType::VARIABLE_DECLARATION}, var_{var_node}, type_{type_node} {}
VariableNode *VarDeclNode::get_var_node() const noexcept { return var_; }
TypeNode *VarDeclNode::get_type_node() const noexcept { return type_; }

BlockNode::BlockNode(std::vector<VarDeclNode *> &&declarations, CompoundStatementNode *compound_statement)
    : AstNode{AstNodeType::BLOCK}, declarations_{std::move(declarations)}, compound_statement_{compound_statement} {}
std::vector<VarDeclNode *> BlockNode::get_declaration_nodes() const noexcept { return declarations_; }
CompoundStatementNode *BlockNode::get_compound_statement_node() const noexcept { return compound_statement_; }

ProgramNode::ProgramNode(const std::string &name, BlockNode *block)
    : AstNode{AstNodeType::PROGRAM}, name_{name}, block_{block} {}
ProgramNode::ProgramNode(std::string &&name, BlockNode *block)
    : AstNode{AstNodeType::PROGRAM}, name_{std::move(name)}, block_{block} {}
const std::string &ProgramNode::get_name() const noexcept { return name_; }
BlockNode *ProgramNode::get_block_node() const noexcept { return block_; }

AssignmentStatementNode::AssignmentStatementNode(VariableNode *lhs, AstNode *rhs)
    : AstNode{AstNodeType::ASSIGNMENT_STATEMENT}, lhs_{lhs}, rhs_{rhs} {}
VariableNode *AssignmentStatementNode::get_lhs() const noexcept { return lhs_; }
AstNode *AssignmentStatementNode::get_rhs() const noexcept { return rhs_; }

NoOperationNode::NoOperationNode() : AstNode{AstNodeType::NO_OPERATION} {}

// BinaryOperatorNode::BinaryOperatorNode(Token *token, AstNode *lhs, AstNode *rhs)
//     : AstNode{AstNodeType::BINARY_OPERATOR}, token_{token}, lhs_{lhs}, rhs_{rhs} {}
BinaryOperatorNode::BinaryOperatorNode(Token *token, AstNode *lhs, AstNode *rhs)
    : TokenHolderNode{AstNodeType::BINARY_OPERATOR, token}, lhs_{lhs}, rhs_{rhs} {}
// BinaryOperatorNode::~BinaryOperatorNode() { delete token_; }
// Token *BinaryOperatorNode::get_token() const noexcept { return token_; }
AstNode *BinaryOperatorNode::get_lhs() const noexcept { return lhs_; }
AstNode *BinaryOperatorNode::get_rhs() const noexcept { return rhs_; }

// UnaryOperatorNode::UnaryOperatorNode(Token *token, AstNode *rhs)
//     : AstNode{AstNodeType::UNARY_OPERATOR}, token_{token}, rhs_{rhs} {}
UnaryOperatorNode::UnaryOperatorNode(Token *token, AstNode *rhs)
    : TokenHolderNode{AstNodeType::UNARY_OPERATOR, token}, rhs_{rhs} {}
// UnaryOperatorNode::~UnaryOperatorNode() { delete token_; }
// Token *UnaryOperatorNode::get_token() const noexcept { return token_; }
AstNode *UnaryOperatorNode::get_rhs() const noexcept { return rhs_; }

// IntNumNode::IntNumNode(IntNumToken *token) : AstNode{AstNodeType::INT_NUM}, token_{token} {}
IntNumNode::IntNumNode(IntNumToken *token) : TokenHolderNode{AstNodeType::INT_NUM, token} {}
// IntNumNode::~IntNumNode() { delete token_; }
// IntNumToken *IntNumNode::get_token() const noexcept { return token_; }

// RealNumNode::RealNumNode(RealNumToken *token) : AstNode{AstNodeType::REAL_NUM}, token_{token} {}
RealNumNode::RealNumNode(RealNumToken *token) : TokenHolderNode{AstNodeType::REAL_NUM, token} {}
// RealNumNode::~RealNumNode() { delete token_; }
// RealNumToken *RealNumNode::get_token() const noexcept { return token_; }

const std::string &map_ast_node_type_to_string(AstNodeType type)
{
    static const std::unordered_map<AstNodeType, std::string> typeToString = {
        {AstNodeType::PROGRAM, "PROGRAM"},
        {AstNodeType::BLOCK, "BLOCK"},
        {AstNodeType::COMPOUND_STATEMENT, "COMPOUND_STATEMENT"},
        {AstNodeType::VARIABLE_DECLARATION, "VARIABLE_DECLARATION"},
        {AstNodeType::ASSIGNMENT_STATEMENT, "ASSIGNMENT_STATEMENT"},
        {AstNodeType::BINARY_OPERATOR, "BINARY_OPERATOR"},
        {AstNodeType::UNARY_OPERATOR, "UNARY_OPERATOR"},
        {AstNodeType::VARIABLE, "VARIABLE"},
        {AstNodeType::TYPE, "TYPE"},
        {AstNodeType::INT_NUM, "INT_NUM"},
        {AstNodeType::REAL_NUM, "REAL_NUM"},
        {AstNodeType::NO_OPERATION, "NO_OPERATION"}};

    static const std::string unknown = "UNKNOWN AST NODE";

    auto it = typeToString.find(type);
    return (it != typeToString.end()) ? it->second : unknown;
}