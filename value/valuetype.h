/**
 *      @file value/valuetype.h
 *      @brief defines ValueType which is used to keep track of type of Value objects
 *      @author Anastasia Sokol
**/

#ifndef VALUE_VALUETYPE_H
#define VALUE_VALUETYPE_H

enum class ValueType {
    numeric,
    string,
    boolean,
    function
};

#endif