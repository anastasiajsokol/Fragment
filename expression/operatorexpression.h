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

        /**
         *  @brief create an operator expression
         *  @param position of first token in expression
         *  @param type of operation to perform
         *  @param arguments to apply operation on 
        **/
        OperatorExpression(const Token::TokenPosition&, OperatorType, std::list<Expression::expression_t>);

        /**
         *  @brief apply operator on arguments
         *  @param state of program 
        **/
        Value::value_t operator ()(ProgramState&) const;
    
    private:
        OperatorType type;                              // keep track of what kind of operation this represents
        std::list<Expression::expression_t> arguments;  // arguments to given operation
};

#endif