#ifndef VALUE_NUMERIC_H
#define VALUE_NUMERIC_H

#include "value.hpp"

struct Numeric : public Value {
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