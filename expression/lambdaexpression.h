/**
 *      @file expression/lambdaexpression.h
 *      @brief defines a lambda expression
 *      @author Anastasia Sokol
**/

#ifndef EXPRESSION_LAMBDAEXPRESSION_H
#define EXPRESSION_LAMBDAEXPRESSION_H

#include "expression.hpp"   // defines Expression

#include <list>             // used to represent a collection of paramater names

/**
 *  @brief represents a nameless function as an expression 
**/
struct LambdaExpression : public Expression {
    public:
        /**
         *  @brief create a lambda expression
         *  @param position of first token
         *  @param parameters the function accepts
         *  @param body of expression 
        **/
        LambdaExpression(const Token::TokenPosition&, std::list<std::string>, expression_t);

        /**
         *  @brief access the underlying function value_t
         *  @param state of program 
        **/
        Value::value_t operator ()(ProgramState&) const;

    private:
        const std::list<std::string> parameters;  // represents the parameters the function accepts
        const expression_t body;                  // represents body of function
};

#endif