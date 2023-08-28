#ifndef DATATYPE_OPERATORTYPE_H
#define DATATYOE_OPERATORTYPE_H

enum class OperatorType {
    _start = 0,
    plus = _start,
    minus,
    multiply,
    divide,
    less_than,
    greater_than,
    less_than_or_equal,
    greater_than_or_equal,
    _end
};

#define NUMBER_OF_OPERATORS ((int)OperatorType::_end - (int)OperatorType::_start)

#endif