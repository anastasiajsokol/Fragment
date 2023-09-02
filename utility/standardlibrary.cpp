#include "standardlibrary.h"

#include "../value/value.hpp"           // defines Value
#include "../value/stringvalue.h"       // defines StringValue
#include "../value/numericvalue.h"      // defines NumericValue
#include "../value/booleanvalue.h"      // defines BooleanValue
#include "../value/notimplemented.hpp"  // defines NotImplemented exception

#include <iostream>     // defines std::cout and std::endl (newline and flush buffer)

#include <cctype>       // defines std::isspace and std::isdigit for pattern matching

Value::value_t flstd::print(std::list<Value::value_t> values){
    std::string output;
    for(const auto &value : values){
        output += (std::string)*value;
    }
    std::cout << output;
    std::cout.flush();
    return Value::value_t(new StringValue(output));
}

Value::value_t flstd::println(std::list<Value::value_t> values){
    std::string output;
    for(const auto &value : values){
        output += (std::string)*value;
    }
    std::cout << output << std::endl;
    return Value::value_t(new StringValue(output));
}

Value::value_t flstd::readline(std::list<Value::value_t> arguments){
    if(arguments.size()){
        throw NotImplemented("'readline' standard library function does not accept arguments");
    }

    std::string line;
    std::getline(std::cin, line);
    return Value::value_t(new StringValue(line));
}

Value::value_t flstd::readnumeric(std::list<Value::value_t> arguments){
    if(arguments.size()){
        throw NotImplemented("'readnumeric' standard library function does not accept arguments");
    }

    std::string line;
    
    while(true) {
        std::cin >> line;

        uint8_t allowed = 1;
        if(std::all_of(line.begin(), line.end(), [&allowed](char v){ return std::isdigit(v) || (v == '.' && --allowed); })){
            break;
        }
    }

    return Value::value_t(new NumericValue(std::stod(line)));
}

Value::value_t flstd::noop(std::list<Value::value_t>){
    return Value::value_t(new BooleanValue(false));
}