#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include "token.hpp"
#include "parser.hpp"
#include "utils.hpp"
#include "ast.hpp"

class ASTNodeVisitor
{
protected:
    std::string _visit(ASTNode *node);
};

class ASTWalker : protected ASTNodeVisitor
{
protected:
    std::string _walk(AST *ast);
};

class Interpreter : protected ASTWalker
{
private:
    Parser *_parser;

public:
    Interpreter(Parser *parser);

    std::string interpret();
};

#endif