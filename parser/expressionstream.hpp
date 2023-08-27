/**
 *      @file parser/expressionstream.hpp
 *      @brief defines template class ExpressionStream in namespace parser for turning a generic stream of blocks into a stream of expressions
 *      @author Anastasia Sokol
**/

#ifndef PARSER_EXPRESSIONSTREAM_H
#define PARSER_EXPRESSIONSTREAM_H

template <typename container_t>
class ExpressionStream {
    private:
        // generic types of container iterator
        typedef decltype(std::declval<container_t>().begin()) stream_iterator_begin_type;
        typedef decltype(std::declval<container_t>().end()) stream_iterator_end_type;

        stream_iterator_begin_type start_of_stream;     // stores iterator to start of container
        stream_iterator_end_type end_of_stream;         // stores end of iterator

    public:
        ExpressionStream();
};

#endif