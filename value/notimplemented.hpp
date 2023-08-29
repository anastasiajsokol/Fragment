/**
 *      @file value/notimplemented.hpp
 *      @brief defines exception for unimplemented operations
 *      @author Anastasia Sokol
**/

#ifndef VALUE_NOTIMPLEMENTED_HPP
#define VALUE_NOTIMPLEMENTED_HPP

#include <stdexcept>    // defines std::runtime_error which NotImplemented extends

struct NotImplemented : public std::runtime_error {
    inline NotImplemented(const std::string &message) : std::runtime_error(message) {}
};

#endif