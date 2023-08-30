#include "stringvalue.h"

#include "numericvalue.h"
#include "booleanvalue.h"
#include "functionvalue.h"
#include "notimplemented.hpp"

#include <functional>

using value_t = Value::value_t;

StringValue::StringValue(const std::string &value) : Value(value) {}

value_t StringValue::operator +(const value_t& other) const noexcept(false){
    switch(other->type){
        case ValueType::numeric:
        case ValueType::string:
        case ValueType::boolean:
            // convert to string then add
            return value_t(new StringValue((std::string)*this + (std::string)*other));

        case ValueType::function:
            // create new function that is the result of the current value of this plus the result of the given function
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return *this + std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
            }));
    }

    throw NotImplemented("Unable to non-type to string");
}

value_t StringValue::operator -(const value_t& other) const noexcept(false){
    throw NotImplemented("Subtracting a value from a string is not defined");
}

value_t StringValue::operator *(const value_t& other) const noexcept(false){
    throw NotImplemented("Multiplying a string by a value is not defined");
}

value_t StringValue::operator /(const value_t& other) const noexcept(false){
    throw NotImplemented("Dividing a string by a value is not defined");
}

value_t StringValue::operator &&(const value_t& other) const noexcept(false) {
    if(other->type == ValueType::function){
        // if function delay as always
        return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
            return *this && std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
        }));
    } else {
        // otherwise cast to booleans then do normal and
        return value_t(new BooleanValue((bool)*this && (bool)*other));
    }
}

value_t StringValue::operator ||(const value_t& other) const noexcept(false) {
    if(other->type == ValueType::function){
        // if function delay as always
        return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
            return *this || std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
        }));
    } else {
        // otherwise cast to booleans then do normal and
        return value_t(new BooleanValue((bool)*this || (bool)*other));
    }
}

value_t StringValue::operator !() const noexcept(false) {
    return value_t(new BooleanValue(!(bool)*this));
}

StringValue::operator std::string() const {
    return std::get<std::string>(this->value);
}

StringValue::operator bool() const {
    return (std::string)*this == "";
}