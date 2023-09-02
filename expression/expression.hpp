/**
 *      @file datatype/expression.hpp
 *      @brief defines Expression base class
 *      @author Anastasia Sokol
**/

#ifndef DATATYPE_EXPRESSION_H
#define DATATYPE_EXPRESSION_H

#include "../value/value.hpp"           // defines Value which is used to represent a loosely typed value of any of Fragment's base value types
#include "../datatype/token.hpp"        // defines Token::TokenPosition used to represent starting position of expression in the file
#include "../datatype/programstate.h"   // defines ProgramState for adding state to otherwise stateless expressions

#include <memory>   // defines std::unqiue_ptr for managing expressions

/**
 *  @brief represents a code expression
**/
struct Expression {
    typedef std::shared_ptr<Expression> expression_t;   // allows for calls to overloaded functions in a memory safe way

    Token::TokenPosition position;  // stores file position of first token in expression

    /**
     *  @brief initialize position to value
     *  @desc while the class Expression is not itself constructable derived classes may call the constructor to initialize position 
    **/
    inline Expression(const Token::TokenPosition &position) : position(position) {}

    /**
     *  @brief enforces that all expression subclasses are evaluatable and that operator () can be called without knowing the specific subtype
     *  @return value representing the value of the expression (note that not all expressions are pure)
    **/
    virtual Value::value_t operator ()(ProgramState&) const = 0;
};

#endif