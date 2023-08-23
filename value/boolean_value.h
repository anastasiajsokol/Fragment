#ifndef FRAGMENT_BOOLEAN_VALUE_H
#define FRAGMENT_BOOLEAN_VALUE_H

#include "value.h"

class BooleanValue {
    private:
        bool value;

    public:
        BooleanValue();
        BooleanValue(const Value&);

        Value operator =(const Value&);

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