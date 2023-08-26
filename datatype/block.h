/**
 *      @file datatype/block.h
 *      @brief defines the Block datatype for generic organization of Tokens
 *      @author Anastasia Sokol
**/

#ifndef DATATYPE_BLOCK_H
#define DATATYPE_BLOCK_H

#include "token.hpp"

#include <variant>
#include <list>

/**
 *  @brief defines a block of tokens which are logically grouped together and which may contain other blocks
**/
struct Block {
    Token::TokenPosition position;
    std::list<std::variant<Token, Block>> view;
};

#endif