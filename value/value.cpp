#include "value.hpp"

#include "notimplemented.hpp"   // defines NotImplemented exception, used heavily

Value::Value(const double value) : value(value) {}
Value::Value(const std::string &value) : value(value) {}
Value::Value(const bool value) : value(value) {}
Value::Value(const std::function<value_t(std::list<value_t>)> &value) : value(value) {}

Value::value_t Value::operator +(const value_t&) const noexcept(false) {
    throw NotImplemented("Addition is not implemented for void type");
}

Value::value_t Value::operator -(const value_t&) const noexcept(false) {
    throw NotImplemented("Subtraction is not implemented for void type");
}

Value::value_t Value::operator *(const value_t&) const noexcept(false) {
    throw NotImplemented("Multiplication is not implemented for void type");
}

Value::value_t Value::operator /(const value_t&) const noexcept(false) {
    throw NotImplemented("Division is not implemented for void type");
}

Value::value_t Value::operator >(const value_t&) const noexcept(false) {
    throw NotImplemented("Comparison is not implemented for void type");
}

Value::value_t Value::operator <(const value_t&) const noexcept(false) {
    throw NotImplemented("Comparison is not implemented for void type");
}

Value::value_t Value::operator >=(const value_t&) const noexcept(false) {
    throw NotImplemented("Comparison is not implemented for void type");
}

Value::value_t Value::operator <=(const value_t&) const noexcept(false) {
    throw NotImplemented("Comparison is not implemented for void type");
}

Value::value_t Value::operator ||(const value_t&) const noexcept(false) {
    throw NotImplemented("Comparison is not implemented for void type");
}

Value::value_t Value::operator &&(const value_t&) const noexcept(false) {
    throw NotImplemented("Comparison is not implemented for void type");
}

Value::value_t Value::operator !() const noexcept(false) {
    throw NotImplemented("Negation is not implemented for void type");
}

Value::operator std::string() const {
    throw NotImplemented("Casting to std::string is not implemented for void type");
}

Value::operator bool() const {
    throw NotImplemented("Casting to boolean is not implemented for void type");
}