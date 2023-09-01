/**
 *      @file utility/standardlibrary.h
 *      @brief defines the (extremely limited) standard library of fragment lisp
 *      @author Anastasia Sokol
**/

#include "../value/value.hpp"   // defines Value

#include <list>                 // defines std::list

namespace flstd {

/**
 *  @brief takes a list of values and prints them out
 *  @param values to print
 *  @return a StringValue containing all the values printed together 
**/
Value::value_t print(std::list<Value::value_t>);

};  // end of namespace flstd