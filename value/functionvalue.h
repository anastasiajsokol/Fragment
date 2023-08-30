#ifndef VALUE_FUNCTIONVALUE_H
#define VALUE_FUNCTIONVALUE_H

#include "value.hpp"

struct FunctionValue : public Value {
    FunctionValue(std::function<Value::value_t(std::list<Value::value_t>)> value);

    value_t operator +(const value_t&) const noexcept(false);
    value_t operator -(const value_t&) const noexcept(false);
    value_t operator *(const value_t&) const noexcept(false);
    value_t operator /(const value_t&) const noexcept(false);

    value_t operator >(const value_t&) const noexcept(false);
    value_t operator <(const value_t&) const noexcept(false);
    value_t operator >=(const value_t&) const noexcept(false);
    value_t operator <=(const value_t&) const noexcept(false);

    value_t operator &(const value_t&) const noexcept(false);
    value_t operator |(const value_t&) const noexcept(false);
    value_t operator !() const noexcept(false);

    operator std::string();
    operator bool();
};

#endif