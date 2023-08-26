/**
 *      @file lexer/token.hpp
 *      @brief defines Token structure to represent the concept of a token and hold debug information
 *      @author Anastasia Sokol
 *          
 *      extended .hpp due to limited use of inline constructors
**/

#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H

#include <stdexcept>    // defines std::runtime_error
#include <string>       // defines std::string

/**
 *  @brief represents symbolic concept of language token
 * 
 *  designed to be a normalized form of language morphemes returned by lexstream 
**/
struct Token {
    /**
     *  @brief alias for refering to type of token morpheme
    **/
    enum class TokenType {
        null,
        end_of_file,
        delimiter,
        numeric,
        keyword,
        operation,
        reference,
        stringliteral,
        boolean
    };

    /**
     *  @brief represents position inside of a file, used for error reporting messages
    **/
    struct TokenPosition {
        ssize_t line;   // file line
        ssize_t index;  // line index

        /**
         *  @brief default construct position to (1, 1), ie the start of the file
         *  @desc this can be used to avoid dealing with setting starting position manually but may also be used to avoid needing to manually construct object
        **/
        inline TokenPosition() : line(1), index(1) {}

        /**
         *  @brief create position from custom starting point
         *  @desc generally there are few cases this might be wanted, but it can be used to represent invalid position (-1, -1)
         *  @param line signed position of line in file, or -1 for invalid line
         *  @param index signed position of token in line
        **/
        inline TokenPosition(const ssize_t line, const ssize_t index) : line(line), index(index) {}
    };

    std::string value;      // used to store the token string value that the token represents
    TokenPosition position; // used to store starting position of token string in input file
    TokenType type;         // tells which language morpheme the token represents

    /**
     *  @brief create token with given characterists
     *  @desc should be used sparringly, in general Token::from_string will do a better job validating the token string, useful for making void or end_of_file tokens
     *  @param value token string value, forwarded to internal constructor
     *  @param position token string position in input file, forwarded to internal constructor
     *  @param type token string type, forwarded to internal constructor
    **/
    inline Token(const std::string& value, const TokenPosition& position, const TokenType type) noexcept : value(value), position(position), type(type) {}
    
    /**
     *  @brief creates default (invalid) token
     *  @desc with a value "Default Constructed" and invalid position and type this does not represent a language morpheme
    **/
    inline Token() noexcept : value("Default Constructed"), position(TokenPosition{-1, -1}), type(TokenType::null) {}
};

/**
 *  @brief convert Token::TokenType into a string representation for development debugging
 *  @param type type to convert to string
**/
std::string to_string(const Token::TokenType type);

#endif