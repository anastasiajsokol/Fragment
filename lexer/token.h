#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H

#include <string>

enum class TokenType {
    end_of_file,
    test
};

struct TokenPosition {
    ssize_t line;
    ssize_t index;
};

struct Token {
    TokenPosition position;
    std::string value;
    TokenType type;
};

#endif