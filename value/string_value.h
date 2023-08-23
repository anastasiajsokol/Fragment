#ifndef FRAGMENT_STRING_VALUE_H
#define FRAGMENT_STRING_VALUE_H

#include "value.h"
#include <string>

class StringValue {
    private:
        std::string value;

    public:
        StringValue();
        StringValue(const Value&);

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