/**
 *      @file datatype/invalidstate.hpp
 *      @brief exception to throw if the program reaches an invalid state (references a reference that does not exist)
 *      @author Anastasia Sokol 
**/

#ifndef DATATYPE_INVALIDSTATE_HPP
#define DATATYPE_INVALIDSTATE_HPP

#include <stdexcept>    // defines std::runtime_error

/**
 *  @brief a wrapper around std::runtime_error for if the program reaches an invalid state 
**/
struct InvalidState : public std::runtime_error {
    /**
     *  @brief create an invalid state
     *  @param message to pass through to std::runtime_error 
    **/
    inline InvalidState(const std::string &message) : std::runtime_error(message) {}
};

#endif