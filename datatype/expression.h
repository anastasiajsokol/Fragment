#ifndef DATATYPE_EXPRESSION_H
#define DATATYPE_EXPRESSION_H

#include "value.h"  // defines Value which is used to represent a loosely typed value of any of Fragment Lisps base value types

/**
 *  @brief represents a code expression
**/
struct Expression {
    /**
     *  @brief enforces that all expression subclasses are evaluatable and that operator () can be called without knowing the specific subtype
     *  @return value representing the value of the expression (note that not all expressions are pure)
    **/
    virtual Value operator ()() = 0;
};

#endif