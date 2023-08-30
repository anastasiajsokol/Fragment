/**
 *      @file value/value.h
 *      @brief defines base class Value for representing weakly typed values
 *      @author Anastasia Sokol
**/

#ifndef DATATYPE_VALUE_H
#define DATATYPE_VALUE_H

#include "valuetype.h"  // defines ValueType used to represent weak type of object

#include <functional>   // defines std::function used to perform magic
#include <list>         // defines std::list used to hold a collection of values
#include <variant>      // defines std::varient a type checked version of a union
#include <memory>       // defines std::shared_ptr used to automatically manage lifetime of values
#include <string>       // defines std::string, needed because std::string must be a complete type to be used in std::variant

/**
 *  @brief base class for weakly typed value implimention
 * 
 *  calling an operation on base class will result in a NotImplemented exception
**/
struct Value {
    typedef std::shared_ptr<Value> value_t; // allows for easy dynamic memory management
    
    std::variant<double, std::string, bool, std::function<value_t(std::list<value_t>)>> value;  // stores generic value of object
    ValueType type; // references what kind of value is being stored at any given time

    /**
     *  @brief extend to initialize value with double
     *  @param value to initialize value to
    **/
    Value(const double value);

    /**
     *  @brief extend to initialize value with string
     *  @param value to initialize value to
    **/
    Value(const std::string &value);

    /**
     *  @brief extend to initialize value with boolean
     *  @param value to initialize value to
    **/
    Value(const bool value);

    /**
     *  @brief extend to initialize value with function
     *  @param value to initialize value to
    **/
    Value(const std::function<value_t(std::list<value_t>)> &value);

    /**
     *  @brief add other to value
     *  @param other value to be added
     *  @return a new value representing this + other
    **/
    virtual value_t operator +(const value_t&) const noexcept(false);

    /**
     *  @brief subtract other to value
     *  @param other value to be subtracted
     *  @return a new value representing this - other
    **/
    virtual value_t operator -(const value_t&) const noexcept(false);

    /**
     *  @brief multiply other to value
     *  @param other value to be multiplied
     *  @return a new value representing this * other
    **/
    virtual value_t operator *(const value_t&) const noexcept(false);

    /**
     *  @brief divide value by other
     *  @param other value to be divided
     *  @return a new value representing this / other
    **/
    virtual value_t operator /(const value_t&) const noexcept(false);

    /**
     *  @brief compare this to other
     *  @param other value to be compared
     *  @return result of comparing this to other
    **/
    virtual value_t operator <(const value_t&) const noexcept(false);

    /**
     *  @brief compare this to other
     *  @param other value to be compared
     *  @return result of comparing this to other
    **/
    virtual value_t operator >(const value_t&) const noexcept(false);

    /**
     *  @brief compare this to other
     *  @param other value to be compared
     *  @return result of comparing this to other
    **/
    virtual value_t operator <=(const value_t&) const noexcept(false);

    /**
     *  @brief compare this to other
     *  @param other value to be compared
     *  @return result of comparing this to other
    **/
    virtual value_t operator >=(const value_t&) const noexcept(false);

    /**
     *  @brief this boolean or other
     *  @param other other value to be or'ed
     *  @return result of this or other
    **/
    virtual value_t operator |(const value_t&) const noexcept(false);

    /**
     *  @brief this boolean and other
     *  @param other other value to be and'ed
     *  @return result of this or other
    **/
    virtual value_t operator &(const value_t&) const noexcept(false);

    /**
     *  @brief boolean not this
     *  @return a value representing not this
    **/
    virtual value_t operator !() const noexcept(false);

    /**
     *  @brief convert to string
    **/
    virtual operator std::string();

    /**
     *  @brief convert to boolean 
    **/
    virtual operator bool();
};

// allow for operations on Value::value_t as if simply of type Value

inline Value::value_t operator +(const Value::value_t& a, const Value::value_t& b){ return *a + b; }
inline Value::value_t operator -(const Value::value_t& a, const Value::value_t& b){ return *a - b; }
inline Value::value_t operator *(const Value::value_t& a, const Value::value_t& b){ return *a * b; }
inline Value::value_t operator /(const Value::value_t& a, const Value::value_t& b){ return *a / b; }
inline Value::value_t operator >(const Value::value_t& a, const Value::value_t& b){ return *a > b; }
inline Value::value_t operator <(const Value::value_t& a, const Value::value_t& b){ return *a < b; }
inline Value::value_t operator >=(const Value::value_t& a, const Value::value_t& b){ return *a >= b; }
inline Value::value_t operator <=(const Value::value_t& a, const Value::value_t& b){ return *a <= b; }
inline Value::value_t operator &(const Value::value_t& a, const Value::value_t& b){ return *a & b; }
inline Value::value_t operator |(const Value::value_t& a, const Value::value_t& b){ return *a | b; }
inline Value::value_t operator !(const Value::value_t& a){ return !(*a); }

#endif