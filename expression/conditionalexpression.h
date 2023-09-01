/**
 *      @file expression/conditionalexpression.h
 *      @brief defines a conditional expression
 *      @author Anastasia Sokol 
**/

#ifndef EXPRESSION_CONDITIONALEXPRESSION_H
#define EXPRESSION_CONDITIONALEXPRESSION_H

#include "expression.hpp"

/**
 *  @brief object representing an expression of the form (if condition true_path false_path) 
**/
struct ConditionalExpression : public Expression {
    public:
        /**
         *  @brief create conditional expression
         *  @param position of first token
         *  @param condition that will be evaluated
         *  @param truthy path taken if condition is truthy
         *  @param falsy path taken if not truthy
        **/
        ConditionalExpression(const Token::TokenPosition&, Expression::expression_t, Expression::expression_t, Expression::expression_t);

        /**
         *  @brief evaluates expression
         *  @return value representing result of path
        **/
        Value::value_t operator ()(ProgramState&) const;

    private:
        Expression::expression_t condition, truthy, falsy;  // used to store the expressions of respective names
};

#endif