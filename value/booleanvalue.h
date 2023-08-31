/**
 *      @file value/booleanvalue.h
 *      @brief implements value interface for boolean types
 *      @author Anastasia Sokol
**/

#ifndef VALUE_BOOLEANVALUE_H
#define VALUE_BOOLEANVALUE_H

#include "value.hpp"    // defines Value interface

/**
 *  @brief boolean value designed to be used in a weakly typed manor with other value types
**/
struct BooleanValue : public Value {
    /**
     *  @brief construct a value object from boolean value
     *  @param value is the boolean value that the object will begin with 
    **/
    BooleanValue(bool value);

    /**
     *  @brief add a value of generic type to this 
     *  @desc see documentation (if existant) for how boolean values interact with other values
    **/
    value_t operator +(const value_t&) const noexcept(false);

    /**
     *  @brief subtract a value of generic type to this 
     *  @desc see documentation (if existant) for how boolean values interact with other values
    **/
    value_t operator -(const value_t&) const noexcept(false);

    /**
     *  @brief multiply a value of generic type to this
     *  @desc see documentation (if existant) for how boolean values interact with other values
    **/
    value_t operator *(const value_t&) const noexcept(false);

    /**
     *  @brief divide a value of generic type to this
     *  @desc see documentation (if existant) for how boolean values interact with other values
    **/
    value_t operator /(const value_t&) const noexcept(false);

    /**
     *  @brief compare boolean to another value type
     *  @desc see documentation (if existant) for how boolean values interact with other values
    **/
    value_t operator >(const value_t&) const noexcept(false);

    /**
     *  @brief compare boolean to another value type
     *  @desc see documentation (if existant) for how boolean values interact with other values
    **/
    value_t operator <(const value_t&) const noexcept(false);

    /**
     *  @brief compare boolean to another value type
     *  @desc see documentation (if existant) for how boolean values interact with other values
    **/
    value_t operator >=(const value_t&) const noexcept(false);

    /**
     *  @brief compare boolean to another value type
     *  @desc see documentation (if existant) for how boolean values interact with other values
    **/
    value_t operator <=(const value_t&) const noexcept(false);

    /**
     *  @brief perform boolean and with another value type
     *  @desc see documentation (if existant) for how boolean values interact with other values
    **/
    value_t operator &&(const value_t&) const noexcept(false);

    /**
     *  @brief perform boolean or with another value type
     *  @desc see documentation (if existant) for how boolean values interact with other values
    **/
    value_t operator ||(const value_t&) const noexcept(false);

    /**
     *  @brief negate this
    **/
    value_t operator !() const noexcept(false);

    /**
     *  @brief returns a string representation of the boolean 
    **/
    operator std::string() const;

    /**
     *  @brief returns boolean type of boolean 
    **/
    operator bool() const;
};

#endif