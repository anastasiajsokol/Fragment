#ifndef VALUE_STRINGVALUE_H
#define VALUE_STRINGVALUE_H

#include "value.hpp"

struct StringValue : public Value {
    StringValue(const std::string &value);

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