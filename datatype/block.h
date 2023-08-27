/**
 *      @file datatype/block.h
 *      @brief defines the Block datatype for generic organization of Tokens
 *      @author Anastasia Sokol
**/

#ifndef DATATYPE_BLOCK_H
#define DATATYPE_BLOCK_H

#include "token.hpp"

#include <type_traits>  // defines std::declval used to get the std::list iterator type
#include <list>         // defines std::list used to store tokens and blocks
#include <variant>      // defines std::varient used to store a mix of tokens and blocks in the same list

/**
 *  @brief defines a block of tokens which are logically grouped together and which may contain other blocks
**/
struct Block {
    // these horrors of types are used so that Block can become iterable by using std::list's iterator
    typedef decltype(std::declval<std::list<std::variant<Token, Block>>>().begin()) list_iterator_begin_type;
    typedef decltype(std::declval<std::list<std::variant<Token, Block>>>().end()) list_iterator_end_type;

    std::list<std::variant<Token, Block>> view; // store ordered collection or tokens and blocks that make up the block
    Token::TokenPosition position;              // store position of first token in block (likely a bracket which should not be stored in view)

    Block(Token::TokenPosition&) noexcept;

    /**
     *  @brief append either a token or another block to this blocks internal view
     *  @throws std::bad_alloc in the case of a failed allocation
    **/
    Block& append(std::variant<Token, Block>) noexcept(false);
    
    /**
     *  @brief equivelent to Block.view.begin()
     *  @return iterater to start of block view
    **/
    list_iterator_begin_type begin() noexcept;

    /**
     *  @brief equivelent to Block.view.end()
     *  @return end of block view iterater
    **/
    list_iterator_end_type end() noexcept;

    /**
     *  @brief get size of view list
     *  @return view.size()
    **/
    size_t size() const noexcept;
};

#endif