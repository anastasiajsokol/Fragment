#ifndef VALUE_BOOLEANVALUE_H
#define VALUE_BOOLEANVALUE_H

#include "value.hpp"

struct BooleanValue : public Value {
    BooleanValue(bool value);

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

    operator std::string() const;
    operator bool() const;
};

#endif