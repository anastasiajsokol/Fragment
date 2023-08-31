/**
 *      @file value/notimplemented.hpp
 *      @brief defines exception for unimplemented operations
 *      @author Anastasia Sokol
**/

#ifndef VALUE_NOTIMPLEMENTED_HPP
#define VALUE_NOTIMPLEMENTED_HPP

#include <stdexcept>    // defines std::runtime_error which NotImplemented extends

/**
 *  @brief exception for attempts to perform operations on types where that operation is not implemeneted
 *  @desc wrapper around std::runtime_error
**/
struct NotImplemented : public std::runtime_error {
    /**
     *  @brief pass message to std::runtime_error constructor
    **/
    inline NotImplemented(const std::string &message) : std::runtime_error(message) {}
};

#endif