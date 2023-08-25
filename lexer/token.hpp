/**
 *      @file lexer/token.hpp
 *      @brief defines LexStream class to convert file path into stream of Tokens
 *      @author Anastasia Sokol
 * 
 *      extended .hpp due to limited use of inline functions
**/

#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H

#include <exception>
#include <stdexcept>    // defines std::runtime_error
#include <string>

struct Token {
    enum class TokenType {
        null,
        end_of_file,
        delimiter,
        numeric,
        keyword,
        operation,
        reference
    };

    struct TokenPosition {
        ssize_t line;
        ssize_t index;

        inline TokenPosition() : line(1), index(1) {}
        inline TokenPosition(ssize_t line, ssize_t index) : line(line), index(index) {}
    };

    struct InvalidTokenString : std::runtime_error {
        TokenPosition position;
        InvalidTokenString(const std::string& message, const TokenPosition& position) : std::runtime_error(message), position(position) {}
    };

    std::string value;
    TokenPosition position;
    TokenType type;

    inline Token(const std::string& value, const TokenPosition& position, TokenType type) noexcept : value(value), position(position), type(type) {}
    inline Token() noexcept : value("Default Constructed"), position(TokenPosition{-1, -1}), type(TokenType::null) {}
    
    static Token from_string(std::string value, TokenPosition position) noexcept(false);
};

const char* to_string(Token::TokenType type);

#endif