/**
 *      @file value/numericvalue.h
 *      @brief defines interface for NumericValue subclass
 *      @author Anastasia Sokol
**/

#ifndef VALUE_NUMERICVALUE_H
#define VALUE_NUMERICVALUE_H

#include "value.hpp"    // defines base class Value

/**
 *  @brief represents a numeric value in a weakly typed way with other value types 
**/
struct NumericValue : public Value {
    /**
     *  @brief construct a numeric value with given value
     *  @desc calls Value double overloaded constructor 
    **/
    NumericValue(double value);

    /**
     *  @brief add a value of generic type to this 
     *  @desc see documentation (if existant) for how numeric values interact with other values
    **/
    value_t operator +(const value_t&) const noexcept(false);

    /**
     *  @brief subtract a value of generic type to this 
     *  @desc see documentation (if existant) for how numeric values interact with other values
    **/
    value_t operator -(const value_t&) const noexcept(false);

    /**
     *  @brief multiply a value of generic type to this
     *  @desc see documentation (if existant) for how numeric values interact with other values
    **/
    value_t operator *(const value_t&) const noexcept(false);

    /**
     *  @brief divide a value of generic type to this
     *  @desc see documentation (if existant) for how numeric values interact with other values
    **/
    value_t operator /(const value_t&) const noexcept(false);

    /**
     *  @brief compare numeric to another value type
     *  @desc see documentation (if existant) for how numeric values interact with other values
    **/
    value_t operator >(const value_t&) const noexcept(false);

    /**
     *  @brief compare numeric to another value type
     *  @desc see documentation (if existant) for how numeric values interact with other values
    **/
    value_t operator <(const value_t&) const noexcept(false);

    /**
     *  @brief compare numeric to another value type
     *  @desc see documentation (if existant) for how numeric values interact with other values
    **/
    value_t operator >=(const value_t&) const noexcept(false);

    /**
     *  @brief compare numeric to another value type
     *  @desc see documentation (if existant) for how numeric values interact with other values
    **/
    value_t operator <=(const value_t&) const noexcept(false);

    /**
     *  @brief perform boolean and with another value type
     *  @desc see documentation (if existant) for how numeric values interact with other values
    **/
    value_t operator &&(const value_t&) const noexcept(false);

    /**
     *  @brief perform boolean or with another value type
     *  @desc see documentation (if existant) for how numeric values interact with other values
    **/
    value_t operator ||(const value_t&) const noexcept(false);

    /**
     *  @brief negate this
    **/
    value_t operator !() const noexcept(false);

    /**
     *  @brief returns a string representation of the numeric 
    **/
    operator std::string() const;

    /**
     *  @brief returns boolean representation of numeric 
    **/
    operator bool() const;
};

#endif