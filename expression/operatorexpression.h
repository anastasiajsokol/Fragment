/**
 *      @file datatype/operatorexpression.h
 *      @brief defines the OperatorExpression type for all expressions of the form (operator expression*)
 *      @author Anastasia Sokol
**/

#ifndef DATATYPE_OPERATOREXPRESSION_H
#define DATATYPE_OPERATOREXPRESSION_H

#include "expression.hpp"   // Expression base class
#include <list>             // defines std::list used to store collection of arguments

struct OperatorExpression : public Expression {
    enum class OperatorType {
        plus,
        minus,
        multiply,
        divide,
        less_than,
        greater_than,
        less_than_or_equal,
        greater_than_or_equal
    };
    
    OperatorType type;                  // used to store type of operation to perform
    std::list<Expression> arguments;    // used to store arguments to expression (all arguments are themselves expressions)

    /**
     *  @brief construct an OperatorExpression with given properties
     *  @param position a copy of the position object is made in the Expression base class
     *  @param type type of operator, used to decide which operation to perform on the arguments
     *  @param arguments a list of expressions which serve as arguments to the operator, recommended to be std::move'd to avoid creating a copy of the passed list
    **/
    OperatorExpression(const Token::TokenPosition &position, const OperatorExpression::OperatorType type, const std::list<Expression> arguments);

    /**
     *  @brief overloads general Expression operator (), performs operation over arguments
     *  @return result of performing operation on all expression arguments
    **/
    Value operator ()();
};

#endif