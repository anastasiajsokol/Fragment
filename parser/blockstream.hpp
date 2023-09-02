/**
 *      @file parser/blockstream.hpp
 *      @brief defines template class BlockStream to convert a token stream into a stream of block objects
 *      @author Anastasia Sokol
**/

#ifndef PARSER_BLOCKSTREAM_H
#define PARSER_BLOCKSTREAM_H

#include "../datatype/block.h"              // defines Block used to represent a collection of tokens in a structured way
#include "../utility/iteratetypeguard.h"    // defines only_if_iterator_type used to restrict container_t typename 
#include "invalidblock.hpp"                 // defines exception parser::InvalidBlock for reporting token streams that do not represent valid blocks

namespace parser {

/**
 *  @brief convert a stream of tokens into a stream of block objects
 * 
 *  designed to be used as a c++ standard container for transforming tokens into blocks
 *  possibily read once depending on storage class, read only
 *  can not be copied !! if you need a second copy (for some reason, probably doing something wrong) then create a completely new instance
 *  however, the class can be moved using std::move
**/
template <typename container_t, only_if_iterater_type(container_t, const Token)>
class BlockStream {
    private:
        // generic types of container iterator
        typedef decltype(std::declval<container_t>().begin()) stream_iterator_begin_type;
        typedef decltype(std::declval<container_t>().end()) stream_iterator_end_type;

        stream_iterator_begin_type start_of_stream;     // stores iterator to start of container
        stream_iterator_end_type end_of_stream;         // stores end of iterator

    public:
        /**
         *  @brief read only, read once iterator for BlockStream - returns blocks
         * 
         *  iterates over token stream, returning blocks as it goes
         *  uses sentenial value for end comparison (specifically, a block containing a single token with type Token::TokenType::end_of_file)
        **/
        struct BlockStreamIterator {
            private:
                stream_iterator_begin_type stream;              // current position in stream
                const stream_iterator_end_type end_of_stream;   // end of stream, used to determine end of stream

                Block cursor;   // keep track of current Block, set in constructor

                /**
                 *  @brief attempt to read a token from stream, return std::nullopt if stream == end_of_stream
                 *  @return an optional constant token reference
                **/
                const Token next(){
                    Token value = *stream;
                    
                    if(stream != end_of_stream){
                        ++stream;
                    }

                    return value;
                }
                
                /**
                 *  @brief attempts to read a complete block from stream
                 *  @desc uses next() to recursively read a blocks until the top level block is formed, or an exception state is reached
                 *  @return a block object representing structure or with end_of_file token if end of stream reached without starting a block
                **/
                Block read_block_from_stream(bool is_starting_block = true) noexcept(false) {
                    // read first token of block
                    Token token = next();
                    
                    // handle special case of starting block
                    if(is_starting_block){
                        // end of file is ok for starting block, return end of stream value
                        if(token.type == Token::TokenType::end_of_file){
                            return Block(token.position).append(token);
                        }

                        // if not end of file, must begin with openning delimiter
                        if(!(token.type == Token::TokenType::delimiter && token.value == "(")){
                            throw InvalidBlock("Top level expression blocks must begin with an opening delimiter '('", token.position);
                        }

                        // advance token so that the rest of the function can act like a non-top level block expression
                        token = next();
                    }

                    Block block(token.position);

                    while(!(token.value == ")" && token.type == Token::TokenType::delimiter)){
                        if(token.type == Token::TokenType::end_of_file){
                            throw InvalidBlock("Unexpected end of file: unclosed expression block scope", token.position);
                        } else if(token.type == Token::TokenType::delimiter && token.value == "("){
                            block.append(read_block_from_stream(false));
                        } else {
                            block.append(token);
                        }
                        token = next();
                    }

                    return block;
                }

            public:
                using iterator_category = std::input_iterator_tag;
                using difference_type   = void;
                using value_type        = Block;
                using pointer           = value_type*;
                using reference         = value_type&;
                
                /**
                 *  @brief create iterator from streams
                 *  @desc moves iterators and loads first block
                 *  @param begin - ing of stream
                 *  @param end of stream
                */
                BlockStreamIterator(stream_iterator_begin_type begin, stream_iterator_end_type end) : stream(std::move(begin)), end_of_stream(std::move(end)) {
                    ++*this; // set cursor to first block
                }
                
                /**
                 *  @brief increment cursor to next block
                 *  @desc calls read_block_from_stream
                 *  @return reference to stream 
                **/
                BlockStreamIterator& operator ++() noexcept(false) {
                    cursor = read_block_from_stream();
                    return *this;
                }

                /**
                 *  @brief access block cursor
                 *  @desc pointer is invalidated after a call to operator ++()
                 *  @return a constant pointer to the block cursor 
                **/
                inline const Block* operator ->() const noexcept {
                    return &cursor;
                }

                /**
                 *  @brief access block cursor
                 *  @desc reference is invalidated after a call to operator ++()
                 *  @return a constant reference to the block cursor 
                **/
                inline const Block& operator *() const noexcept {
                    return cursor;
                }

                /**
                 *  @brief check if block has one element with end_of_file token and that cursor is the same
                 *  @param block the value to check if end_of_file token
                 *  @return bool signifing if the end of the stream has been reached 
                **/
                inline bool operator ==(const Block& block) const {
                    return block.size() == 1 && block.size() == cursor.size() && std::holds_alternative<Token>(block.view.front()) && std::holds_alternative<Token>(cursor.view.front()) && std::get<Token>(block.view.front()).type == Token::TokenType::end_of_file && std::get<Token>(cursor.view.front()).type == Token::TokenType::end_of_file;
                }

                /**
                 *  @brief not operator ==
                 *  @return bool representing the negation of operator ==
                **/
                inline bool operator !=(const Block& block) const {
                    return !(*this == block);
                }
        };

        /**
         *  @brief construct BlockStream with given container
         *  @param container object that will have .begin() and .end() called on it
        **/
        BlockStream(container_t container) : start_of_stream(container.begin()), end_of_stream(container.end()) {}

        /**
         *  @brief get iterator to start of block stream, only ensured to be valid once
         *  @return iterator to start of block stream
        **/
        BlockStreamIterator begin(){
            return BlockStreamIterator(std::move(start_of_stream), std::move(end_of_stream));
        }

        /**
         *  @brief ending value for block stream iterator
         *  @return returns a block with only one token of type end_of_stream
        **/
        const Block end() const {
            return Block(Token::TokenPosition{-1, -1}).append(Token("End of File", Token::TokenPosition{-1, -1}, Token::TokenType::end_of_file));
        }
};

} // end of namespace parser

#endif