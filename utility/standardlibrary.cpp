#include "standardlibrary.h"

#include "../value/value.hpp"       // defines Value
#include "../value/stringvalue.h"   // defines StringValue

#include <iostream>     // defines std::cout and std::endl (newline and flush buffer)

Value::value_t flstd::print(std::list<Value::value_t> values){
    std::string output;
    for(const auto &value : values){
        output += (std::string)*value;
    }
    std::cout << output;
    return Value::value_t(new StringValue(output));
}

Value::value_t flstd::println(std::list<Value::value_t> values){
    std::string output;
    for(const auto &value : values){
        output += (std::string)*value;
    }
    std::cout << output << std::endl;
    return Value::value_t(new StringValue(output + '\n'));
}