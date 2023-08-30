#include "functionvalue.h"

#include "numericvalue.h"
#include "stringvalue.h"
#include "booleanvalue.h"
#include "notimplemented.hpp"

#include <functional>

using value_t = Value::value_t;

FunctionValue::FunctionValue(std::function<value_t(std::list<value_t>)> value) : Value(value) {}

value_t FunctionValue::operator +(const value_t& other) const noexcept(false){
    switch(other->type){
        case ValueType::numeric:
        case ValueType::string:
        case ValueType::boolean:
            // create new function that is the result of the current value of this plus the result of the given function
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return std::get<std::function<value_t(std::list<value_t>)>>(this->value)(arguments) + other;
            }));
        
        case ValueType::function:
            // create new function that is the result of the current value of this plus the result of the given function
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return std::get<std::function<value_t(std::list<value_t>)>>(this->value)(arguments) + std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
            }));
    }

    throw NotImplemented("Unable to add function value to a non-type");
}

value_t FunctionValue::operator -(const value_t& other) const noexcept(false){
    switch(other->type){
        case ValueType::numeric:
        case ValueType::string:
        case ValueType::boolean:
            // create new function that is the result of the current value of this plus the result of the given function
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return std::get<std::function<value_t(std::list<value_t>)>>(this->value)(arguments) - other;
            }));
        
        case ValueType::function:
            // create new function that is the result of the current value of this plus the result of the given function
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return std::get<std::function<value_t(std::list<value_t>)>>(this->value)(arguments) - std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
            }));
    }

    throw NotImplemented("Unable to subtract non-type from function value");
}

value_t FunctionValue::operator *(const value_t& other) const noexcept(false){
    switch(other->type){
        case ValueType::numeric:
        case ValueType::string:
        case ValueType::boolean:
            // create new function that is the result of the current value of this plus the result of the given function
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return std::get<std::function<value_t(std::list<value_t>)>>(this->value)(arguments) * other;
            }));
        
        case ValueType::function:
            // create new function that is the result of the current value of this plus the result of the given function
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return std::get<std::function<value_t(std::list<value_t>)>>(this->value)(arguments) * std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
            }));
    }

    throw NotImplemented("Unable to multiply function value and non-type");
}

value_t FunctionValue::operator /(const value_t& other) const noexcept(false){
    switch(other->type){
        case ValueType::numeric:
        case ValueType::string:
        case ValueType::boolean:
            // create new function that is the result of the current value of this plus the result of the given function
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return std::get<std::function<value_t(std::list<value_t>)>>(this->value)(arguments) / other;
            }));
        
        case ValueType::function:
            // create new function that is the result of the current value of this plus the result of the given function
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return std::get<std::function<value_t(std::list<value_t>)>>(this->value)(arguments) / std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
            }));
    }

    throw NotImplemented("Unable to divide function value by non-type");
}

value_t FunctionValue::operator &&(const value_t& other) const noexcept(false){
    switch(other->type){
        case ValueType::numeric:
        case ValueType::string:
        case ValueType::boolean:
            // create new function that is the result of the current value of this plus the result of the given function
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return std::get<std::function<value_t(std::list<value_t>)>>(this->value)(arguments) && other;
            }));
        
        case ValueType::function:
            // create new function that is the result of the current value of this plus the result of the given function
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return std::get<std::function<value_t(std::list<value_t>)>>(this->value)(arguments) && std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
            }));
    }

    throw NotImplemented("Unable to 'and' function value and non-type");
}

value_t FunctionValue::operator ||(const value_t& other) const noexcept(false){
    switch(other->type){
        case ValueType::numeric:
        case ValueType::string:
        case ValueType::boolean:
            // create new function that is the result of the current value of this plus the result of the given function
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return std::get<std::function<value_t(std::list<value_t>)>>(this->value)(arguments) || other;
            }));
        
        case ValueType::function:
            // create new function that is the result of the current value of this plus the result of the given function
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return std::get<std::function<value_t(std::list<value_t>)>>(this->value)(arguments) || std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
            }));
    }

    throw NotImplemented("Unable to 'or' function value and non-type");
}

value_t FunctionValue::operator !() const noexcept(false){
    return value_t(new FunctionValue([*this](std::list<value_t> arguments) -> value_t {
        return !(std::get<std::function<value_t(std::list<value_t>)>>(this->value)(arguments));
    }));
}

FunctionValue::operator std::string() const {
    return "λ(...)";
};

FunctionValue::operator bool() const {
    return true;
}