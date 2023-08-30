#ifndef VALUE_NUMERICVALUE_H
#define VALUE_NUMERICVALUE_H

#include "value.hpp"

struct NumericValue : public Value {
    NumericValue(double value);

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