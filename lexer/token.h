#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H

#include <string>

enum class TokenType {
    end_of_file
};

struct TokenPosition {
    size_t line;
    size_t index;
};

struct Token {
    TokenPosition position;
    std::string value;
    TokenType type;
};

#endif