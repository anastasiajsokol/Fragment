/**
 *      @file expression/operatorexpression.h
 *      @brief defines interface for expressions matching operater in grammar.md
 *      @author Anastasia Sokol 
**/

#ifndef EXPRESSION_OPERATOREXPRESSION_H
#define EXPRESSION_OPERATOREXPRESSION_H

#include "expression.hpp"   // defines Expression base class

struct OperatorExpression : public Expression {
    public:
        enum class OperatorType {
            operator_add,
            operator_subtract,
            operator_multiply,
            operator_divide,
            operator_less,
            operator_greater,
            operator_less_or_equal,
            operator_greater_or_equal,
            operator_and,
            operator_or,
            operator_not
        };

        OperatorExpression(const Token::TokenPosition&, OperatorType, std::list<Expression::expression_t>);

        Value::value_t operator ()(ProgramState&) const;
    
    private:
        OperatorType type;
        std::list<Expression::expression_t> arguments;
};

#endif