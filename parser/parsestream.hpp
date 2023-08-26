/**
 *  @file parser/parsestream.h
 *  @brief defines the ParseStream class for forming expression trees
 *  @author Anastasia Sokol
 * 
 *  parse generic container holding tokens into expression tree
 *  templated class
**/

#ifndef PARSER_PARSESTREAM_H
#define PARSER_PARSESTREAM_H

#include "../lexer/token.hpp"

#include <optional>

template<typename container_t, typename = std::enable_if_t<std::is_same_v<typename container_t::value_type, Token>>>
class ParseStream {
    private:
        auto items;
        auto end_of_stream;

        std::optional<Token> next(){
            if(items == end_of_stream){
                return std::nullopt;
            }
            return ++items;
        }

    public:
        inline ParseStream(container_t &tokens) : items(tokens.begin()), end_of_stream(tokens.end()) {}
};

#endif