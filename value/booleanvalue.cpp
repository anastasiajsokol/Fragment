#include "booleanvalue.h"

#include "numericvalue.h"
#include "stringvalue.h"
#include "functionvalue.h"
#include "notimplemented.hpp"

#include <functional>

using value_t = Value::value_t;

BooleanValue::BooleanValue(bool value) : Value(value) {}

value_t BooleanValue::operator +(const value_t& other) const noexcept(false) {
    switch(other->type){
        case ValueType::numeric:
            // 1 bit modular arithmetic is the same as xor
            // note that this makes it the same as numeric + boolean
            // warning: (bool)other != (bool)*other
            return value_t(new BooleanValue((bool)*this ^ (bool)*other));
        
        case ValueType::string:
            // convert boolean to string then add
            return value_t(new StringValue((std::string)*this + (std::string)*other));
        
        case ValueType::boolean:
            // 1 bit modular arithmetic => xor
            return value_t(new BooleanValue((bool)*this ^ (bool)*other));
        
        case ValueType::function:
            // create new function that is the result of the current value of this plus the result of the given function
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return *this + std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
            }));
    }

    throw NotImplemented("Unable to add non-type to boolean");
}

value_t BooleanValue::operator -(const value_t& other) const noexcept(false) {
    switch(other->type){
        case ValueType::numeric:
            // 1 bit modular subtraction
            // warning: (bool)other != (bool)*other
            return value_t(new BooleanValue((bool)*other ? !(bool)*this : (bool)*this));
        
        case ValueType::string:
            throw NotImplemented("Unable to subtract string from boolean");
        
        case ValueType::boolean:
            // 1 bit modular subtraction
            return value_t(new BooleanValue((bool)*other ? !(bool)*this : (bool)*this));
        
        case ValueType::function:
            // create new function that is the result of the current value of this minus the result of the given function
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return *this - std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
            }));
    }

    throw NotImplemented("Unable to subtract non-type from boolean");
}

value_t BooleanValue::operator *(const value_t& other) const noexcept(false) {
    switch(other->type){
        case ValueType::numeric:
            return value_t(new NumericValue((bool)*this ? std::get<double>(other->value) : 0.0));
        
        case ValueType::string:
            return value_t(new StringValue((bool)*this ? std::get<std::string>(other->value) : ""));
        
        case ValueType::boolean:
            // 1 bit modular multiplication => and
            return value_t(new BooleanValue((bool)*this && (bool)*other));
        
        case ValueType::function:
            // create new function that is the result of the current value of this times the result of the given function
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return *this * std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
            }));
    }

    throw NotImplemented("Unable to multiply non-type and boolean");
}

value_t BooleanValue::operator /(const value_t& other) const noexcept(false) {
    switch(other->type){
        case ValueType::numeric:
            throw NotImplemented("Division of a boolean by a numeric is not allowed");
        
        case ValueType::string:
            throw NotImplemented("Division of a boolean by a string is not allowed");
        
        case ValueType::boolean:
            throw NotImplemented("Division of a boolean by a boolean is not allowed");
        
        case ValueType::function:
            throw NotImplemented("Since division of a boolean by any time is not allowed, neither is division by a generic function");
    }

    throw NotImplemented("Unable to divide a non-type from a boolean");
}

value_t BooleanValue::operator &&(const value_t& other) const noexcept(false) {
    if(other->type == ValueType::function){
        // create new function that is the result of the current value of this and the result of the given function
        return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
            return *this && std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
        }));
    } else {
        return value_t(new BooleanValue((bool)*this && (bool)*other));
    }
}

value_t BooleanValue::operator ||(const value_t& other) const noexcept(false) {
    if(other->type == ValueType::function){
        // create new function that is the result of the current value of this and the result of the given function
        return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
            return *this || std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
        }));
    } else {
        return value_t(new BooleanValue((bool)*this || (bool)*other));
    }
}

value_t BooleanValue::operator !() const noexcept(false) {
    return value_t(new BooleanValue(!(bool)*this));
}

BooleanValue::operator std::string() const {
    return (bool)*this ? "true" : "false";
}

BooleanValue::operator bool() const {
    return std::get<bool>(this->value);
}