#include "numericvalue.h"

#include "stringvalue.h"
#include "booleanvalue.h"
#include "functionvalue.h"
#include "notimplemented.hpp"

#include <iomanip>          // std::setprecision
#include <functional>       // defines std::function

#include <cmath>            // defines std::modf


using value_t = Value::value_t;

NumericValue::NumericValue(double value) : Value(value) {}

value_t NumericValue::operator +(const value_t& other) const noexcept(false){
    switch(other->type){
        case ValueType::numeric:
            // normal numeric addition
            return value_t(new NumericValue(std::get<double>(value) + std::get<double>(other->value)));
        
        case ValueType::string:
            // convert this to string first, then add as strings
            return value_t(new StringValue((std::string)*this + (std::string)*other));
        
        case ValueType::boolean:
            // 1 bit modular arithmetic is the same as xor
            return value_t(new BooleanValue((bool)*this ^ (bool)*other));
        
        case ValueType::function:
            // create new function that is the result of the current value of this plus the result of the given function
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return *this + std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
            }));
    }

    throw NotImplemented("Unable to add numeric value to a non-type");
}

value_t NumericValue::operator -(const value_t& other) const noexcept(false) {
    switch(other->type){
        case ValueType::numeric:
            // normal numeric subtraction
            return value_t(new NumericValue(std::get<double>(value) - std::get<double>(other->value)));
        
        case ValueType::string:
            // does not make logical sense
            throw NotImplemented("Unable to subtract a string from a numeric");
        
        case ValueType::boolean:
            // 1 bit modular subtraction
            return value_t(new BooleanValue((bool)*other ? !(bool)*this : (bool)*this));
        
        case ValueType::function:
            // create new function that is the result of the current value of this minus the result of the given function
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return *this - std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
            }));
    }

    throw NotImplemented("Unable to subtract non-type from numeric");
}

value_t NumericValue::operator *(const value_t& other) const noexcept(false) {
    switch(other->type){
        case ValueType::numeric:
            // normal numeric multiplication
            return value_t(new NumericValue(std::get<double>(value) * std::get<double>(other->value)));
        
        case ValueType::string:
            // string appearing n times in a row, if negative then reversed
            {
                ssize_t n = std::get<double>(value);

                bool reverse = n < 0 ? n = -n : false;

                std::string temporary;
                
                temporary.reserve(n * std::get<std::string>(other->value).length());
                
                for(size_t i = 0; i < n; ++i){
                    temporary += std::get<std::string>(other->value);
                }

                if(reverse){
                    std::reverse(temporary.begin(), temporary.end());
                }

                return value_t(new StringValue(std::move(temporary)));
            }

        case ValueType::boolean:
            // boolean multiplication is the same as the 'and' operation
            return value_t(new BooleanValue((bool)*this && (bool)*other));
        
        case ValueType::function:
            // create new function that is the result of the current value of this multiplied by the result of the given function
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return *this * std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
            }));
    }

    throw NotImplemented("Unable to multiply numeric value by a non-type");
}

value_t NumericValue::operator /(const value_t& other) const noexcept(false){
    switch(other->type){
        case ValueType::numeric:
            // normal numeric division
            return value_t(new NumericValue(std::get<double>(value) / std::get<double>(other->value)));
        
        case ValueType::string:
            // no logical definition
            throw NotImplemented("Unable to divide numeric type by string");
        
        case ValueType::boolean:
            // no logical definition (or... at least not one that is consistent with the other operations)
            throw NotImplemented("Unable to divide numeric by boolean");

        case ValueType::function:
            // create new function that is the result of the current value of this divided by the result of the given function
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return *this / std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
            }));
    }

    throw NotImplemented("Unable to divide numeric value by a non-type");
}

value_t NumericValue::operator >(const value_t& other) const noexcept(false) {
    switch(other->type){
        case ValueType::numeric:
            // normal numeric comparison
            return value_t(new BooleanValue(std::get<double>(value) > std::get<double>(other->value)));
        
        case ValueType::string:
            // no real logical definition
            throw NotImplemented("Unable to compare numeric and string");
        
        case ValueType::boolean:
            // check if resulting booleans are the same
            return value_t(new BooleanValue((bool)*this > (bool)*this));
        
        case ValueType::function:
            // create new function that checks if result is less than current value
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return *this > std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
            }));
    }

    throw NotImplemented("Unable to compare numeric value and a non-type");
}

value_t NumericValue::operator <(const value_t& other) const noexcept(false) {
    switch(other->type){
        case ValueType::numeric:
            // normal numeric comparison
            return value_t(new BooleanValue(std::get<double>(value) < std::get<double>(other->value)));
        
        case ValueType::string:
            // no real logical definition
            throw NotImplemented("Unable to compare numeric and string");
        
        case ValueType::boolean:
            // check if resulting booleans are the same
            return value_t(new BooleanValue((bool)*this < (bool)*other));
        
        case ValueType::function:
            // create new function that checks if result is less than current value
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return *this < std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
            }));
    }

    throw NotImplemented("Unable to compare numeric value and a non-type");
}

value_t NumericValue::operator >=(const value_t& other) const noexcept(false) {
    switch(other->type){
        case ValueType::numeric:
            // normal numeric comparison
            return value_t(new BooleanValue(std::get<double>(value) >= std::get<double>(other->value)));
        
        case ValueType::string:
            // no real logical definition
            throw NotImplemented("Unable to compare numeric and string");
        
        case ValueType::boolean:
            // check if resulting booleans are the same
            return value_t(new BooleanValue((bool)*this >= (bool)*other));
        
        case ValueType::function:
            // create new function that checks if result is less than current value
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return *this >= std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
            }));
    }

    throw NotImplemented("Unable to compare numeric value and a non-type");
}

value_t NumericValue::operator <=(const value_t& other) const noexcept(false) {
    switch(other->type){
        case ValueType::numeric:
            // normal numeric comparison
            return value_t(new BooleanValue(std::get<double>(value) <= std::get<double>(other->value)));
        
        case ValueType::string:
            // no real logical definition
            throw NotImplemented("Unable to compare numeric and string");
        
        case ValueType::boolean:
            // check if resulting booleans are the same
            return value_t(new BooleanValue((bool)*this <= (bool)*other));
        
        case ValueType::function:
            // create new function that checks if result is less than current value
            return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
                return *this <= std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
            }));
    }

    throw NotImplemented("Unable to compare numeric value and a non-type");
}

value_t NumericValue::operator &&(const value_t& other) const noexcept(false) {
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

value_t NumericValue::operator ||(const value_t& other) const noexcept(false) {
    if(other->type == ValueType::function){
        // if function delay as always
        return value_t(new FunctionValue([*this, other /* captures both by value */](std::list<value_t> arguments) -> value_t {
            return *this || std::get<std::function<value_t(std::list<value_t>)>>(other->value)(arguments);
        }));
    } else {
        // otherwise cast to booleans then do normal or
        return value_t(new BooleanValue((bool)*this || (bool)*other));
    }
}

value_t NumericValue::operator !() const noexcept(false) {
    return value_t(new BooleanValue(!(bool)*this));
}

NumericValue::operator std::string() const {
    double intg;
    if(std::modf(std::get<double>(value), &intg) == 0.0){
        std::stringstream ss;
        ss << std::fixed << std::setprecision(0) << intg;
        return ss.str();
    } else {
        return std::to_string(std::get<double>(value));
    }
}

NumericValue::operator bool() const {
    return std::get<double>(value);
}