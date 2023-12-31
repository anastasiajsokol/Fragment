/**
 *      @file utility/standardlibrary.h
 *      @brief defines the (extremely limited) standard library of Fragment
 *      @author Anastasia Sokol
**/

#include "../value/value.hpp"   // defines Value

#include <list>                 // defines std::list

namespace frstd {

/**
 *  @brief takes a list of values and prints them out
 *  @param values to print
 *  @return a StringValue containing all the values printed together 
**/
Value::value_t print(std::list<Value::value_t>);

/**
 *  @brief takes a list of values and prints them out with trailing newline
 *  @param values to print
 *  @return a StringValue containing all the values printed together
**/
Value::value_t println(std::list<Value::value_t>);

/**
 *  @brief read a line from the user
 *  @param values must be an empty list
 *  @return line read from user
**/
Value::value_t readline(std::list<Value::value_t>);

/**
 *  @brief read a number from the user
 *  @param values must be an empty list or a default value for if the user does not enter a number
 *  @return number read from user
**/
Value::value_t readnumeric(std::list<Value::value_t>);

}  // end of namespace frstd