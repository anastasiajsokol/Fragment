/**
 *      @file datatype/programstate.h
 *      @brief defines ProgramState structure which can be passed to expressions
 *      @author Anastasia Sokol 
**/

#ifndef DATATYPE_PROGRAMSTATE_H
#define DATATYPE_PROGRAMSTATE_H

#include "../value/value.hpp"   // defines Value::value_t which is the type references are mapped to

#include <unordered_map>        // defines std::unordered_map used to make reference lookups
#include <vector>               // defines std::vector used to manage scope

/**
 *  @brief used to manage state to otherwise stateless expressions
**/
struct ProgramState {
    private:
        std::vector<std::unordered_map<std::string, Value::value_t>> scope; // stores references in a way that can be managed by scope

    public:
        /**
         *  @brief initializes state to be global scope 
        **/
        ProgramState();

        /**
         *  @brief create a new scope 
        **/
        void push();

        /**
         *  @brief remove top scope 
        **/
        void pop();

        /**
         *  @brief set reference to value in *top scope*
         *  @param name string representing name of reference
         *  @param value value_t representing the value stored by reference
         *  @return value_t just set
        **/
        Value::value_t set(const std::string&, Value::value_t);
        
        /**
         *  @brief get value stored by reference starting at current scope going down
         *  @param name string representing name of reference
         *  @return value_t refered to by given string
         *  @throw InvalidState if reference not found
        **/
        Value::value_t get(const std::string&) const noexcept(false);
};

#endif