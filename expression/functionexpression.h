/**
 *      @file expression/functionexpression.h
 *      @brief defines FunctionExpression structure
 *      @author Anastasia Sokol 
**/

#ifndef EXPRESSION_FUNCTIONEXPRESSION_H
#define EXPRESSION_FUNCTIONEXPRESSION_H

#include "expression.hpp"   // defines Expression

#include <list>             // defines std::list for storing arguments

struct FunctionExpression : public Expression {
    public:
        /**
         *  @brief create function expression for given function
         *  @param position of first token
         *  @param function expression that (after being evaluated itself) will be passed arguments
         *  @param arguments to pass to function 
        **/
        FunctionExpression(const Token::TokenPosition&, Expression::expression_t, std::list<Expression::expression_t>);

        /**
         *  @brief evaluate function with provided arguments
         *  @param state of program 
        **/
        Value::value_t operator ()(ProgramState&) const;

    private:
        Expression::expression_t function;
        std::list<Expression::expression_t> arguments;
};

#endif