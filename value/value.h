#ifndef FRAGMENT_VALUE_H
#define FRAGMENT_VALUE_H

enum class ValueType {
    numeric,
    function,
    boolean,
    string
};

class Value {
    public:
        ValueType type;

        virtual Value operator =(const Value&);

        virtual Value& operator +=(const Value&);
        virtual Value& operator -=(const Value&);
        virtual Value& operator *=(const Value&);
        virtual Value& operator /=(const Value&);

        virtual Value operator +(const Value&);
        virtual Value operator -(const Value&);
        virtual Value operator *(const Value&);
        virtual Value operator /(const Value&);

        virtual Value operator >=(const Value&);
        virtual Value operator <=(const Value&);
        virtual Value operator >(const Value&);
        virtual Value operator <(const Value&);

        virtual Value operator ==(const Value&);
        virtual Value operator !=(const Value&);

        virtual Value operator &(const Value&);
        virtual Value operator |(const Value&);
        virtual Value operator ~();

        virtual operator bool();
};

#endif