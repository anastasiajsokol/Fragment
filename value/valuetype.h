/**
 *      @file value/valuetype.h
 *      @brief defines ValueType which is used to keep track of type of Value objects
 *      @author Anastasia Sokol
**/

#ifndef VALUE_VALUETYPE_H
#define VALUE_VALUETYPE_H

#include <string>   // defines std::string

enum class ValueType {
    numeric,
    string,
    boolean,
    function
};

std::string to_string(ValueType type);

#endif