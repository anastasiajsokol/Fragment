/**
 *      @file expression/defineexpression.h
 *      @brief defines the keyword 'define' expression
 *      @author Anastasia Sokol 
**/

#ifndef EXPRESSION_DEFINEEXPRESSION_H
#define EXPRESSION_DEFINEEXPRESSION_H

#include "expression.hpp"   // defines Expression

struct DefineExpression : public Expression {
    public:
        DefineExpression(const Token::TokenPosition&, const std::string&, expression_t);

        Value::value_t operator ()(ProgramState&) const;
    
    private:
        const std::string &name;
        expression_t value;
};

#endif