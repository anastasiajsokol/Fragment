/**
 *      @file parser/blockstream.hpp
 *      @brief defines LexStream class to convert a token stream into a stream of block objects
 *      @author Anastasia Sokol
 * 
 *      TODO: impliment
**/

#ifndef PARSER_BLOCKSTREAM_H
#define PARSER_BLOCKSTREAM_H

#include "../datatype/block.h"

#include <stdexcept>    // defines std::runtime_error used for BlockStreamDoubleReadException
#include <optional>     // defines std::optional for operations that may reach an end of stream

namespace parser {

/**
 *  @brief convert a stream of tokens into a stream of block objects
 * 
 *  designed to be used as a c++ standard container for transforming tokens into blocks
 *  possibily read once depending on storage class, read only
 *  can not be copied !! if you need a second copy (for some reason, probably doing something wrong) then create a completely new instance
 *  however, the class can be moved using std::move
**/
template <typename container_t>
class BlockStream {
    private:
        // generic types of container iterator
        typedef decltype(std::declval<container_t>().begin()) stream_iterator_begin_type;
        typedef decltype(std::declval<container_t>().end()) stream_iterator_end_type;

        const stream_iterator_begin_type start_of_stream;   // stores iterator to start of container
        const stream_iterator_end_type end_of_stream;       // stores end of iterator

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
                std::optional<const Token&> next();

                /**
                 *  @brief attempts to read a complete block from stream
                 *  @desc uses next() to recursively read a blocks until the top level block is formed, or an exception state is reached
                 *  @return a block object representing structure or with end_of_file token if end of stream reached without starting a block
                **/
                Block read_block_from_stream() noexcept(false);

            public:
                /**
                 *  @brief create iterator from container
                 *  @desc uses passed container to construct iterater, note that what happens will depend on container type
                */
                BlockStreamIterator(container_t);
                
                /**
                 *  @brief increment cursor to next block
                 *  @desc calls read_block_from_stream
                 *  @return reference to stream 
                **/
                BlockStreamIterator& operator ++() noexcept(false);

                /**
                 *  @brief access block cursor
                 *  @desc pointer is invalidated after a call to operator ++()
                 *  @return a constant pointer to the block cursor 
                **/
                const Block* operator ->() const noexcept;

                /**
                 *  @brief access block cursor
                 *  @desc reference is invalidated after a call to operator ++()
                 *  @return a constant reference to the block cursor 
                **/
                const Block& operator *() const noexcept;

                /**
                 *  @brief check if block has one element with end_of_file token and that cursor is the same
                 *  @return bool signifing if the end of the stream has been reached 
                **/
                bool operator ==(const Block&);

                /**
                 *  @brief not operator ==
                 *  @return bool representing the negation of operator ==
                **/
                bool operator !=(const Block&);
        };

        /**
         *  @brief construct BlockStream with given container
         *  @param container object that will have .begin() and .end() called on it
        **/
        BlockStream(container_t);

        /**
         *  @brief get iterator to start of block stream, only ensured to be valid once
         *  @return iterator to start of block stream
        **/
        BlockStreamIterator begin();

        /**
         *  @brief ending value for block stream iterator
         *  @return returns a block with only one token of type end_of_stream
        **/
        Block end() const;
};

}; // end of namespace parser

#endif