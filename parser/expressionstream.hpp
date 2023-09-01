/**
 *      @file parser/expressionstream.hpp
 *      @brief defines template class ExpressionStream in namespace parser for turning a generic stream of blocks into a stream of expressions
 *      @author Anastasia Sokol
**/

#ifndef PARSER_EXPRESSIONSTREAM_H
#define PARSER_EXPRESSIONSTREAM_H

#include "../datatype/block.h"                  // defines Block which is the type this class converts into expressions
#include "../utility/iteratetypeguard.h"        // defines only_if_iterater_type used to restrict generic containter_t template type
#include "../expression/invalidexpression.hpp"  // defines InvalidExpression exception
#include "../expression/expression.hpp"         // defines Expression which is the base return type
#include "../expression/selfexpression.h"       // defines SelfExpression
#include "../expression/atomicexpression.h"     // defines AtomicExpression
#include "../expression/defineexpression.h"     // defines DefineExpression

namespace parser {

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

                std::variant<Value::value_t, std::string> value_from_token(const Token &token){

                }

                Expression::expression_t atomic_expression_from_token(const Token &token){
                    std::variant<Value::value_t, std::string> value = value_from_token(token);
                    if(std::holds_alternative<Value::value_t>(value)){
                        return exp_t(new  AtomicExpression(std::get<Token>(token.position, std::get<Value::value_t>(value))));
                    } else {
                        return exp_t(new  AtomicExpression(std::get<Token>(token.position, std::get<std::string>(value))));
                    }
                }

                /**
                 *  @brief read next expression from stream
                 *  @desc recursively reads expressions into the top level expression, then returns
                 *  @return Expression::expression_t representing next expression in input stream 
                **/
                Expression::expression_t read_block_into_expression(const Block &block){
                    /**
                     *  this code implements the grammar
                     *  I apologize for how messy it is
                     *  it could perhaps be split up where each case has another function that actually implements it
                     *  but... this works
                    **/

                    using exp_t = Expression::expression_t;

                    if(block.size() == 1){
                        // must be a self expression

                        bool token = std::holds_alternative<Token>(block.view.front()); // check if token or block

                        if(token){
                            // token inside block
                            return exp_t(new SelfExpression(block.position, atomic_expression_from_token(std::get<Token>(block.view.front()))));
                        } else {
                            // block inside block
                            return exp_t(new SelfExpression(block.position, read_block_into_expression(std::get<Block>(block.view.front()))));
                        }
                    }

                    if(std::holds_alternative<Token>(block.view.front()) && std::get<Token>(block.view.front()).type == Token::TokenType::keyword){
                        // must be a keyword expression (either define, lambda, or conditional)
                        
                        std::string keyword = std::get<Token>(block.view.front()).value;

                        if(keyword == "define"){
                            if(block.size() != 3){
                                throw InvalidExpression(block.position, "The 'define' expression expects only 2 parameters; a reference and a sub expression. Got " + std::to_string(block.size() - 1));
                            }

                            auto members = block.view.begin();
                            
                            std::variant<Token, Block> name = *++members;
                            std::variant<Token, Block> value = *++members;

                            if(!std::holds_alternative<Token>(name) || std::get<Token>(name).type != Token::TokenType::reference){
                                throw InvalidExpression(block.position, "Expected the first parameter to 'define' expression to be a reference");
                            }

                            return exp_t(new DefineExpression(block.position, std::get<Token>(name).value, std::holds_alternative<Token>(value) ?
                                    atomic_expression_from_token(std::get<Token>(value))
                                :   read_block_into_expression(std::get<Block>(value))
                            ));
                        } else if(keyword == "lambda"){
                            
                        } else if(keyword == "if"){

                        } else {
                            throw InvalidExpression(block.position, "Expected keyword from token but got value [" + keyword + "] (likely internal parsing error)");
                        }
                    }



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
                ExpressionStreamIterator& operator ++() noexcept(false) {
                    cursor = read_expression_from_stream(*stream);
                    ++stream;
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
                inline bool operator !=(const Expression::expression_t &other) const noexcept {
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

};  // end of namespace parser

#endif