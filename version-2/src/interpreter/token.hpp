#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <ostream>
#include <string>

constexpr char kNull = '\0';
constexpr char kWhitespace = ' ';
constexpr char kPlus = '+';
constexpr char kMinus = '-';
constexpr char kMul = '*';
constexpr char kForwardSlash = '/';
constexpr char kDot = '.';
constexpr char kColon = ':';
constexpr char kSemiColon = ';';
constexpr char kEqualsSign = '=';
constexpr char kComma = ',';
constexpr char kLeftCurlyBrace = '{';
constexpr char kRightCurlyBrace = '}';
constexpr char kLParen = '(';
constexpr char kRParen = ')';

constexpr const char *kBegin = "BEGIN";
constexpr const char *kEnd = "END";
constexpr const char *kProgram = "PROGRAM";
constexpr const char *kVar = "VAR";
constexpr const char *kInteger = "INTEGER";
constexpr const char *kReal = "REAL";

/// @brief Token types
enum class TokenType : unsigned char
{
    // MARK: Reserved keywords

    BEGIN,
    END,
    PROGRAM,
    VAR,
    INTEGER,
    REAL,

    // MARK: Arithmetic operator

    ASSIGN,
    PLUS,
    MINUS,
    MUL,
    FLOAT_DIV,
    INTEGER_DIV,

    // MARK: Special characters

    DOT,
    COLON,
    SEMI_COLON,
    COMMA,
    LPAREN,
    RPAREN,

    ID,
    INTEGER_CONST,
    REAL_CONST,

    /// @brief EOF (end-of-file) token is used to indicate that
    /// there is no more input left for lexical analysis
    END_OF_FILE
};

static const std::string &map_token_type_to_string(const TokenType &token_type);

class Token
{
public:
    explicit Token(TokenType type);

    /// @brief Retrieve the type of the token
    TokenType get_type() const noexcept;
    /// @note The overloaded << operator function must then be declared as a friend of class Token
    /// so it can access the private data within a Token object
    friend std::ostream &operator<<(std::ostream &os, const Token &token);

protected:
    TokenType type_;
};

#endif