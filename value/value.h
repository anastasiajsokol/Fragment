/**
 *      @file value/value.h
 *      @brief defines base class Value for representing weakly typed values
 *      @author Anastasia Sokol
**/

#ifndef DATATYPE_VALUE_H
#define DATATYPE_VALUE_H

#include "valuetype.h"

#include <functional>   // defines std::function used to perform magic
#include <list>         // defines std::list used to hold a collection of values
#include <variant>      // defines std::varient a type checked version of a union
#include <memory>       // defines std::shared_ptr used to automatically manage lifetime of values

struct Value {
    typedef std::shared_ptr<Value> value_t;
    
    std::variant<double, std::string, bool, std::function<value_t(std::list<value_t>)>> value;
    ValueType type;

    virtual value_t operator +(const value_t& other) const noexcept(false);
};

#endif