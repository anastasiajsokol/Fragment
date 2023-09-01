/**
 *      @file expression/atomicexpression.h
 *      @brief defines AtmicExpression structure
 *      @author Anastasia Sokol 
**/

#ifndef EXPRESSION_ATOMICEXPRESSION_H
#define EXPRESSION_ATOMICEXPRESSION_H

#include "expression.hpp"   // defines Expression

#include <variant>          // defines std::variant used to store an ambigious Value::value_t or std::string reference name

struct AtomicExpression : public Expression {
    public:
        /**
         *  @brief create atomic expression with given value
         *  @param position of first token
         *  @param value to set expression to 
        **/
        AtomicExpression(const Token::TokenPosition &, Value::value_t);

        /**
         *  @brief create abstract atomic expression with reference
         *  @param position of first token
         *  @param reference name to lookup value of when called 
        **/
        AtomicExpression(const Token::TokenPosition &, std::string);

        /**
         *  @brief get the atomic value stored in expression
         *  @param state of current program (used to lookup references) 
        **/
        Value::value_t operator ()(ProgramState&) const;

    private:
        bool reference;                                     // stores if this stores a value or a reference to a value
        std::variant<Value::value_t, std::string> value;    // either a value or a reference to a value
};

#endif