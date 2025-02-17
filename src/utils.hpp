#ifndef UTILS_HPP
#define UTILS_HPP

#define __THROW_PARSING_ERROR \
    throw std::runtime_error("Error parsing input");

constexpr char NULL_CHAR = '\0';
constexpr char WHITESPACE_CHAR = ' ';
constexpr char PLUS_CHAR = '+';
constexpr char MINUS_CHAR = '-';
constexpr char MUL_CHAR = '*';
constexpr char DIV_CHAR = '/';
constexpr char LPAREN_CHAR = '(';
constexpr char RPAREN_CHAR = ')';

/// @brief Token types
enum class TokenType
{
    INTEGER,

    PLUS,
    MINUS,
    MUL,
    DIV,
    LPAREN,
    RPAREN,

    /// @brief EOF (end-of-file) token is used to indicate that
    /// there is no more input left for lexical analysis
    END_OF_FILE
};

#endif