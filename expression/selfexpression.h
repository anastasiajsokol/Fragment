/**
 *      @file expression/selfexpression.h
 *      @brief defines SelfExpression structure
 *      @author Anastasia Sokol 
**/

#ifndef EXPRESSION_SELFEXPRESSION_H
#define EXPRESSION_SELFEXPRESSION_H

#include "expression.hpp"   // defines Expression

/**
 *  @brief represents an ambigious reference between a reference to a value and a reference to a function with no arguments 
**/
struct SelfExpression : public Expression {
    public:
        /**
         *  @brief create a 'self expression'
         *  @param position of first token
         *  @param value that may be a function (in which case evaluated with no arguments) or a pure value (passed through) 
        **/
        SelfExpression(const Token::TokenPosition&, Expression::expression_t);

        /**
         *  @brief evaluate 'self expression'
         *  @param state of program 
        **/
        Value::value_t operator ()(ProgramState&) const;

    private:
        Expression::expression_t value;
};

#endif