#ifndef DATATYPE_VALUETYPE_H
#define DATATYPE_VALUETYPE_H

enum class ValueType {
    _start = 0,
    numeric = _start,
    _end
};

#define NUMBER_OF_VALUE_TYPES ((int)ValueType::_end - (int)ValueType::_start)

#endif