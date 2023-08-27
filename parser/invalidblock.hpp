/**
 *      @file parser/invalidblock.hpp
 *      @brief define exception for block construction errors
 *      @author Anastasia Sokol
**/

#ifndef PARSER_INVALIDBLOCK_H
#define PARSER_INVALIDBLOCK_H

#include "../datatype/token.hpp"    // defines Token::TokenPosition which is used to track lexeme position in file

#include <stdexcept>                // defines std::runtime_error which is extended for InvalidLexeme

namespace parser {

/**
 *  @brief used to report an invalid block construction
**/
struct InvalidBlock : std::runtime_error {
    Token::TokenPosition position; // represent position of offending lexeme in the input file

    /**
     *  @brief construct InvalidBlock exception
     *  @desc forwards message to std::runtime_error and stores position internally
     *  @param message description of what makes the block invalid
     *  @param position the position of the block in the input file (from token)
    **/
    inline InvalidBlock(const std::string& message, const Token::TokenPosition& position) noexcept : std::runtime_error(message), position(position) {}
};

}; // end of namespace parser

#endif