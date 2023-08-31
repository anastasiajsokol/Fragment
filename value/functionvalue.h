/**
 *      @file value/functionvalue.h
 *      @brief implements value interface for function types
 *      @author Anastasia Sokol
**/

#ifndef VALUE_FUNCTIONVALUE_H
#define VALUE_FUNCTIONVALUE_H

#include "value.hpp"    // defines Value interface

/**
 *  @brief functional value designed to be used in a weakly typed manor with other value types
**/
struct FunctionValue : public Value {
    /**
     *  @brief construct a value object from a callable type
     *  @param value any callable type
    **/
    FunctionValue(std::function<Value::value_t(std::list<Value::value_t>)> value);

    /**
     *  @brief add a value of generic type to this 
     *  @desc see documentation (if existant) for how function values interact with other values
    **/
    value_t operator +(const value_t&) const noexcept(false);

    /**
     *  @brief subtract a value of generic type to this 
     *  @desc see documentation (if existant) for how function values interact with other values
    **/
    value_t operator -(const value_t&) const noexcept(false);

    /**
     *  @brief multiply a value of generic type to this
     *  @desc see documentation (if existant) for how function values interact with other values
    **/
    value_t operator *(const value_t&) const noexcept(false);

    /**
     *  @brief divide a value of generic type to this
     *  @desc see documentation (if existant) for how function values interact with other values
    **/
    value_t operator /(const value_t&) const noexcept(false);

    /**
     *  @brief compare function to another value type
     *  @desc see documentation (if existant) for how function values interact with other values
    **/
    value_t operator >(const value_t&) const noexcept(false);

    /**
     *  @brief compare function to another value type
     *  @desc see documentation (if existant) for how function values interact with other values
    **/
    value_t operator <(const value_t&) const noexcept(false);

    /**
     *  @brief compare function to another value type
     *  @desc see documentation (if existant) for how function values interact with other values
    **/
    value_t operator >=(const value_t&) const noexcept(false);

    /**
     *  @brief compare function to another value type
     *  @desc see documentation (if existant) for how function values interact with other values
    **/
    value_t operator <=(const value_t&) const noexcept(false);

    /**
     *  @brief perform boolean and with another value type
     *  @desc see documentation (if existant) for how function values interact with other values
    **/
    value_t operator &&(const value_t&) const noexcept(false);

    /**
     *  @brief perform boolean or with another value type
     *  @desc see documentation (if existant) for how function values interact with other values
    **/
    value_t operator ||(const value_t&) const noexcept(false);

    /**
     *  @brief negate this
    **/
    value_t operator !() const noexcept(false);

    /**
     *  @brief always returns "λ(...)"s
    **/
    operator std::string() const;

    /**
     *  @brief always returns true
    **/
    operator bool() const;
};

#endif