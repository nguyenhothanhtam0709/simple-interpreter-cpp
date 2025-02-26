#include "parser.hpp"

Parser::Parser(Lexer *lexer) : lexer_{lexer}
{
    current_token_ = lexer_->get_next_token();
}
Parser::~Parser()
{
    delete current_token_;
}