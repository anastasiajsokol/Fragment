/**
 *      @file lexer/exceptions.hpp
 *      @brief define exception for generic lexing error
 *      @author Anastasia Sokol
**/

#ifndef LEXER_EXCEPTIONS_H
#define LEXER_EXCEPTIONS_H

#include "../datatype/token.hpp"    // defines Token::TokenPosition which is used to track lexeme position in file

#include <stdexcept>                // defines std::runtime_error which is extended for InvalidLexeme

namespace lexer {

/**
 *  @brief used to report an invalid lexeme that could not be turned into a token
 * 
 *  example: "123dfbdwe" which is an invalid numeric lexeme
**/
struct InvalidLexeme : std::runtime_error {
    Token::TokenPosition position; // represent position of offending lexeme in the input file

    /**
     *  @brief construct InvalidLexeme exception
     *  @desc forwards message to std::runtime_error and stores position internally
     *  @param message description of what makes the lexeme invalid
     *  @param position the position of the lexeme in the input file
    **/
    inline InvalidLexeme(const std::string& message, const Token::TokenPosition& position) noexcept : std::runtime_error(message), position(position) {}
};

}; // end of namespace lexer

#endif