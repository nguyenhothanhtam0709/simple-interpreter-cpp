#include "ast.hpp"
#include <queue>
#include "ast_node.hpp"

AbstractSyntaxTree::AbstractSyntaxTree(ProgramNode *root) : root_{root} {}
AbstractSyntaxTree::~AbstractSyntaxTree()
{
    if (root_ != nullptr)
    {
        std::queue<AstNode *> nodes;
        nodes.emplace(root_);
        while (!nodes.empty())
        {
            AstNode *current_node = nodes.front();
            nodes.pop();

            switch (current_node->get_type())
            {
            case AstNodeType::PROGRAM:
            {
                ProgramNode *node = static_cast<ProgramNode *>(current_node);
                nodes.emplace(node->get_block_node());
                break;
            }
            case AstNodeType::BLOCK:
            {
                BlockNode *node = static_cast<BlockNode *>(current_node);
                for (auto &declaration_node : node->get_declaration_nodes())
                {
                    nodes.emplace(declaration_node);
                }
                nodes.emplace(node->get_compound_statement_node());
                break;
            }
            case AstNodeType::COMPOUND_STATEMENT:
            {
                CompoundStatementNode *node = static_cast<CompoundStatementNode *>(current_node);
                for (auto &statement_node : node->get_statement_list())
                {
                    nodes.emplace(statement_node);
                }
                break;
            }
            case AstNodeType::VARIABLE_DECLARATION:
            {
                VarDeclNode *node = static_cast<VarDeclNode *>(current_node);
                nodes.emplace(node->get_var_node());
                nodes.emplace(node->get_type_node());
                break;
            }
            case AstNodeType::ASSIGNMENT_STATEMENT:
            {
                AssignmentStatementNode *node = static_cast<AssignmentStatementNode *>(current_node);
                nodes.emplace(node->get_lhs());
                nodes.emplace(node->get_rhs());
                break;
            }
            case AstNodeType::BINARY_OPERATOR:
            {
                BinaryOperatorNode *node = static_cast<BinaryOperatorNode *>(current_node);
                nodes.emplace(node->get_lhs());
                nodes.emplace(node->get_rhs());
                break;
            }
            case AstNodeType::UNARY_OPERATOR:
            {
                UnaryOperatorNode *node = static_cast<UnaryOperatorNode *>(current_node);
                nodes.emplace(node->get_rhs());
                break;
            }
            case AstNodeType::VARIABLE:
            {
                VariableNode *node = static_cast<VariableNode *>(current_node);
                break;
            }
            case AstNodeType::TYPE:
            {
                TypeNode *node = static_cast<TypeNode *>(current_node);
                break;
            }
            case AstNodeType::INT_NUM:
            {
                IntNumNode *node = static_cast<IntNumNode *>(current_node);
                break;
            }
            case AstNodeType::REAL_NUM:
            {
                RealNumNode *node = static_cast<RealNumNode *>(current_node);
                break;
            }
            case AstNodeType::NO_OPERATION:
            {
                NoOperationNode *node = static_cast<NoOperationNode *>(current_node);
                break;
            }
            default:
                throw std::runtime_error("Unknow ast node type");
            }
            delete current_node;
        }
    }
}

ProgramNode *AbstractSyntaxTree::get_root() { return root_; }