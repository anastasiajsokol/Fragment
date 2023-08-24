#ifndef FRAGMENT_FUNCTION_VALUE_H
#define FRAGMENT_FUNCTION_VALUE_H

#include "value.h"

#include <list>

typedef Value value_function_type(const std::list<Value>&);

class FunctionValue {
    private:
        value_function_type* function;

    public:
        FunctionValue();
        FunctionValue(const Value&);

        Value& operator =(const Value&);

        Value operator ()(const std::list<Value>&);

        Value& operator +=(const Value&);
        Value& operator -=(const Value&);
        Value& operator *=(const Value&);
        Value& operator /=(const Value&);

        Value operator +(const Value&);
        Value operator -(const Value&);
        Value operator *(const Value&);
        Value operator /(const Value&);

        Value operator >=(const Value&);
        Value operator <=(const Value&);
        Value operator >(const Value&);
        Value operator <(const Value&);

        Value operator ==(const Value&);
        Value operator !=(const Value&);

        Value operator &(const Value&);
        Value operator |(const Value&);
        Value operator ~();

        operator bool();
};

#endif