/**
 *      @file value/stringvalue.h
 *      @brief defines interface for StringValue subclass
 *      @author Anastasia Sokol
**/

#ifndef VALUE_STRINGVALUE_H
#define VALUE_STRINGVALUE_H

#include "value.hpp"    // defines Value base class

/**
 *  @brief represents a string value in a weakly typed way with other value types 
**/
struct StringValue : public Value {
    /**
     *  @brief construct a string value with given value
     *  @desc calls Value std::string overloaded constructor 
    **/
    StringValue(const std::string &value);

    /**
     *  @brief add a value of generic type to this 
     *  @desc see documentation (if existant) for how string values interact with other values
    **/
    value_t operator +(const value_t&) const noexcept(false);

    /**
     *  @brief subtract a value of generic type to this 
     *  @desc see documentation (if existant) for how string values interact with other values
    **/
    value_t operator -(const value_t&) const noexcept(false);

    /**
     *  @brief multiply a value of generic type to this
     *  @desc see documentation (if existant) for how string values interact with other values
    **/
    value_t operator *(const value_t&) const noexcept(false);

    /**
     *  @brief divide a value of generic type to this
     *  @desc see documentation (if existant) for how string values interact with other values
    **/
    value_t operator /(const value_t&) const noexcept(false);

    /**
     *  @brief compare string to another value type
     *  @desc see documentation (if existant) for how string values interact with other values
    **/
    value_t operator >(const value_t&) const noexcept(false);

    /**
     *  @brief compare string to another value type
     *  @desc see documentation (if existant) for how string values interact with other values
    **/
    value_t operator <(const value_t&) const noexcept(false);

    /**
     *  @brief compare string to another value type
     *  @desc see documentation (if existant) for how string values interact with other values
    **/
    value_t operator >=(const value_t&) const noexcept(false);

    /**
     *  @brief compare string to another value type
     *  @desc see documentation (if existant) for how string values interact with other values
    **/
    value_t operator <=(const value_t&) const noexcept(false);

    /**
     *  @brief perform boolean and with another value type
     *  @desc see documentation (if existant) for how string values interact with other values
    **/
    value_t operator &&(const value_t&) const noexcept(false);

    /**
     *  @brief perform boolean or with another value type
     *  @desc see documentation (if existant) for how string values interact with other values
    **/
    value_t operator ||(const value_t&) const noexcept(false);

    /**
     *  @brief negate this
    **/
    value_t operator !() const noexcept(false);

    /**
     *  @brief returns underlying string
    **/
    operator std::string() const;

    /**
     *  @brief tests if the string is empty
    **/
    operator bool() const;
};

#endif