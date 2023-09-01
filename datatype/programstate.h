/**
 *      @file datatype/programstate.h
 *      @brief defines ProgramState structure which can be passed to expressions
 *      @author Anastasia Sokol 
**/

#ifndef DATATYPE_PROGRAMSTATE_H
#define DATATYPE_PROGRAMSTATE_H

#include "../expression/expression.hpp"     // defines Expression::expression_t which is the type references are mapped to

#include <unordered_map>                    // defines std::unordered_map used to make reference lookups
#include <vector>                           // defines std::vector used to manage scope

/**
 *  @brief used to manage state to otherwise stateless expressions
**/
struct ProgramState {
    private:
        std::vector<std::unordered_map<std::string, Expression::expression_t>> scope; // stores references in a way that can be managed by scope

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
         *  @brief set reference to expression in *top scope*
         *  @param name string representing name of reference
         *  @param value expression_t representing the expression stored by reference
        **/
        void set(std::string, Expression::expression_t);

        /**
         *  @brief get expression stored by reference starting at current scope going down
         *  @param name string representing name of reference
         *  @return expression_t refered to by given string
        **/
        Expression::expression_t get(std::string);
};

#endif