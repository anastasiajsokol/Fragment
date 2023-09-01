/**
 *      @file parser/expressionstream.hpp
 *      @brief defines template class ExpressionStream in namespace parser for turning a generic stream of blocks into a stream of expressions
 *      @author Anastasia Sokol
**/

#ifndef PARSER_EXPRESSIONSTREAM_H
#define PARSER_EXPRESSIONSTREAM_H

#include "../datatype/block.h"              // defines Block which is the type this class converts into expressions
#include "../utility/iteratetypeguard.h"    // defines only_if_iterater_type used to restrict generic containter_t template type
#include "../expression/expression.hpp"     // defines Expression which is the base return type

/**
 *  @brief transforms a stream of blocks into a stream of expressions 
**/
template <typename container_t, only_if_iterater_type(container_t, const Block)>
class ExpressionStream {
    private:
        // generic types of container iterator
        typedef decltype(std::declval<container_t>().begin()) stream_iterator_begin_type;
        typedef decltype(std::declval<container_t>().end()) stream_iterator_end_type;

        stream_iterator_begin_type start_of_stream;     // stores iterator to start of container
        stream_iterator_end_type end_of_stream;         // stores end of iterator

    public:
        struct ExpressionStreamIterator {
            private:
                stream_iterator_begin_type stream;      // stores iterator into container
                stream_iterator_end_type end;           // stores end of iterator

                Expression::expression_t cursor;        // stores current expression

                /**
                 *  @brief read next expression from stream
                 *  @desc recursively reads expressions into the top level expression, then returns
                 *  @return Expression::expression_t representing next expression in input stream 
                **/
                Expression::expression_t read_expression_from_stream(){
                    return Expression::expression_t(nullptr);
                }

            public:
                using iterator_category = std::input_iterator_tag;
                using difference_type   = void;
                using value_type        = Expression::expression_t;
                using pointer           = value_type*;
                using reference         = value_type&;
                
                /**
                 *  @brief create iterator from streams
                 *  @desc moves iterators and loads first expression
                 *  @param begin - ing of stream
                 *  @param end of stream
                */
                ExpressionStreamIterator(stream_iterator_begin_type begin, stream_iterator_end_type end) : stream(std::move(begin)), end(std::move(end)) {
                    ++*this;
                }

                /**
                 *  @brief increment cursor to next block
                 *  @desc calls read_expression_from_stream
                 *  @return reference to stream 
                **/
                BlockStreamIterator& operator ++() noexcept(false) {
                    cursor = read_expression_from_stream();
                    return *this;
                }

                /**
                 *  @brief access expression cursor
                 *  @desc pointer is invalidated after a call to operator ++()
                 *  @return a constant pointer to the expression cursor 
                **/
                inline const Expression::expression_t* operator ->() const noexcept {
                    return &cursor;
                }

                /**
                 *  @brief access expression cursor
                 *  @desc reference is invalidated after a call to operator ++()
                 *  @return a constant reference to the expression cursor 
                **/
                inline const Expression::expression_t& operator *() const noexcept {
                    return cursor;
                }

                /**
                 *  @brief checks if the Expression::expression_t's have the some truthiness
                 *  @return boolean (meant for testing end of stream) 
                **/
                inline bool operator ==(const Expression::expression_t &other) const noexcept {
                    return (bool)cursor == (bool)other;
                }

                /**
                 *  @brief checks if the Expression::expression_t's have different truthiness
                 *  @return boolean (meant for testing end of stream) 
                **/
                inline bool operator ==(const Expression::expression_t &other) const noexcept {
                    return (bool)cursor != (bool)other;
                }
        };

        inline ExpressionStream(container_t container) : start_of_stream(std::move(container.begin())), end_of_stream(std::move(container.end())) {}

        ExpressionStreamIterator begin(){
            return ExpressionStreamIterator(std::move(start_of_stream), std::move(end_of_stream));
        }

        const Expression::expression_t end() const noexcept {
            return Expression::expression_t(nullptr);
        }
};

#endif