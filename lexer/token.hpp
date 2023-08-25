#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H

#include <string>

enum class TokenType {
    end_of_file,
    null,

    delimiter,

    test
};

const char* to_string(TokenType type);

struct TokenPosition {
    ssize_t line;
    ssize_t index;

    inline TokenPosition() : line(1), index(1) {}
    inline TokenPosition(ssize_t line, ssize_t index) : line(line), index(index) {}
};

struct Token {
    std::string value;
    TokenPosition position;
    TokenType type;

    Token(const std::string& value, const TokenPosition& position, TokenType type) : value(value), position(position), type(type) {}
    Token() : value("Default Constructed"), position(TokenPosition{-1, -1}), type(TokenType::null) {}
    
    static Token from_string(std::string value, TokenPosition position);
};

#endif