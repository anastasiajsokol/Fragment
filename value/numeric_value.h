#ifndef FRAGMENT_NUMERIC_VALUE_H
#define FRAGMENT_NUMERIC_VALUE_H

#include "value.h"

class NumericValue {
    private:
        double value;

    public:
        NumericValue();
        NumericValue(const double&);

        Value& operator =(const Value&);

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