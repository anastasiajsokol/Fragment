/**
 *      @file expression/invalidexpression.hpp
 *      @brief defines a wrapper around std::runtime_error that also stors token position
 *      @author Anastasia Sokol 
**/

#ifndef EXPRESSION_INVALIDEXPRESSION_HPP
#define EXPRESSION_INVALIDEXPRESSION_HPP

#include "../datatype/token.hpp"    // defines Token::TokenPosition

#include <stdexcept>                // defines std::runtime_error

/**
 *  @brief thrown if attempt to create (or potentially use) invalid expression 
**/
struct InvalidExpression : public std::runtime_error {
    Token::TokenPosition position;  // stores position of first token in expression

    /**
     *  @brief create invalid expression exception
     *  @param position of first token in expression
     *  @param message to pass to std::runtime_error 
    **/
    inline InvalidExpression(const Token::TokenPosition &position, const std::string &message) : std::runtime_error(message), position(position) {}
};

#endif