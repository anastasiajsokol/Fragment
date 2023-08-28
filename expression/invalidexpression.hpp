#ifndef EXPRESSION_INVALIDEXPRESSION_HPP
#define EXPRESSION_INVALIDEXPRESSION_HPP

#include "../datatype/token.hpp"    // defines Token::TokenPosition

#include <stdexcept>                // defines std::runtime_error

struct InvalidExpression : public std::runtime_error {
    Token::TokenPosition position;

    inline InvalidExpression(const Token::TokenPosition &position, const std::string &message) : std::runtime_error(message), position(position) {}
};

#endif