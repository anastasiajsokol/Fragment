/**
 *      @file parser/expressionstream.hpp
 *      @brief defines template class ExpressionStream in namespace parser for turning a generic stream of blocks into a stream of expressions
 *      @author Anastasia Sokol
**/

#ifndef PARSER_EXPRESSIONSTREAM_H
#define PARSER_EXPRESSIONSTREAM_H

#include "../datatype/block.h"                      // defines Block which is the type this class converts into expressions
#include "../utility/iteratetypeguard.h"            // defines only_if_iterater_type used to restrict generic containter_t template type
#include "../expression/invalidexpression.hpp"      // defines InvalidExpression exception
#include "../expression/expression.hpp"             // defines Expression which is the base return type
#include "../expression/selfexpression.h"           // defines SelfExpression
#include "../expression/atomicexpression.h"         // defines AtomicExpression
#include "../expression/defineexpression.h"         // defines DefineExpression
#include "../expression/lambdaexpression.h"         // defines LambdaExpression
#include "../expression/conditionalexpression.h"    // defines ConditionalExpression
#include "../expression/operatorexpression.h"       // defines OperatorExpression and OperatorExpression::OperatorType
#include "../expression/functionexpression.h"       // defines FunctionExpression
#include "../value/numericvalue.h"                  // defines NumericValue
#include "../value/booleanvalue.h"                  // defines BooleanValue
#include "../value/stringvalue.h"                   // defines StringValue


#include <algorithm>                            // defines std::all_of for pattern matching

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
                    using tt = Token::TokenType;
                    using vt = Value::value_t;

                    if(token.type == tt::reference){
                        return token.value;
                    }

                    if(token.type == tt::numeric){
                        return vt(new NumericValue(std::stod(token.value)));
                    } else if(token.type == tt::boolean){
                        return vt(new BooleanValue(token.value == "true"));
                    } else if(token.type == tt::stringliteral){
                        return vt(new StringValue(token.value));
                    }

                    throw InvalidExpression(token.position, "Expected a valued token but got a token of type [" + to_string(token.type) + "]");
                }

                Expression::expression_t atomic_expression_from_token(const Token &token){
                    using exp_t = Expression::expression_t;
                    std::variant<Value::value_t, std::string> value = value_from_token(token);
                    if(std::holds_alternative<Value::value_t>(value)){
                        return exp_t(new AtomicExpression(token.position, std::get<Value::value_t>(value)));
                    } else {
                        return exp_t(new AtomicExpression(token.position, std::get<std::string>(value)));
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
                                throw InvalidExpression(block.position, "The 'define' expression expects 2 parameters; a reference and a sub expression. Got " + std::to_string(block.size() - 1));
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
                            if(block.size() != 3){
                                throw InvalidExpression(block.position, "The 'lambda' expression expects 2 parameters; a set of references and a body expression. Got " + std::to_string(block.size() - 1));
                            }

                            auto members = block.view.begin();
                            
                            std::variant<Token, Block> parameters = *++members;
                            std::variant<Token, Block> body = *++members;

                            if(!std::holds_alternative<Block>(parameters)){
                                throw InvalidExpression(block.position, "lambda expressions require that the first parameter is a set of references");
                            }

                            if(!std::all_of(std::get<Block>(parameters).begin(), std::get<Block>(parameters).end(), [](std::variant<Token, Block> value) -> bool { return std::holds_alternative<Token>(value) && std::get<Token>(value).type == Token::TokenType::reference; })){
                                throw InvalidExpression(block.position, "lambda expressions require that the first parameter is a set of references");
                            }

                            Expression::expression_t body_expression = std::holds_alternative<Token>(body) ? atomic_expression_from_token(std::get<Token>(body)) : read_block_into_expression(std::get<Block>(body));

                            std::list<std::string> named_parameters;
                            for(const auto &param : std::get<Block>(parameters)){
                                named_parameters.push_back(std::get<Token>(param).value);
                            }

                            return exp_t(new LambdaExpression(block.position, std::move(named_parameters), body_expression));
                        } else if(keyword == "if"){
                            if(block.size() != 4){
                                throw InvalidExpression(block.position, "The 'if' conditional expression expects 3 parameters; a condition, a path for true, and a path for false. Got " + std::to_string(block.size() - 1));
                            }

                            auto members = block.view.begin();
                            
                            std::variant<Token, Block> condition = *++members;
                            std::variant<Token, Block> truthy = *++members;
                            std::variant<Token, Block> falsy = *++members;

                            auto cpath = std::holds_alternative<Token>(condition) ? atomic_expression_from_token(std::get<Token>(condition)) : read_block_into_expression(std::get<Block>(condition));
                            auto tpath = std::holds_alternative<Token>(truthy) ? atomic_expression_from_token(std::get<Token>(truthy)) : read_block_into_expression(std::get<Block>(truthy));
                            auto fpath = std::holds_alternative<Token>(falsy) ? atomic_expression_from_token(std::get<Token>(falsy)) : read_block_into_expression(std::get<Block>(falsy));

                            return exp_t(new ConditionalExpression(block.position, cpath, tpath, fpath));
                        } else {
                            throw InvalidExpression(block.position, "Expected keyword from token but got value [" + keyword + "] (likely internal parsing error)");
                        }
                    }

                    if(std::holds_alternative<Token>(block.view.front()) && std::get<Token>(block.view.front()).type == Token::TokenType::operation){
                        // must be an operation expression
                        // note that operator expression constructor does some error handling for us in regards to number of arguments
                        
                        std::list<Expression::expression_t> parameters;

                        for(auto it = ++block.view.begin(); it != block.view.end(); ++it){
                            parameters.push_back(std::holds_alternative<Token>(*it) ? atomic_expression_from_token(std::get<Token>(*it)) : read_block_into_expression(std::get<Block>(*it)));
                        }

                        using optype = OperatorExpression::OperatorType;

                        std::string operation = std::get<Token>(block.view.front()).value;

                        switch(operation[0]){
                            case '+':
                                return exp_t(new OperatorExpression(block.position, optype::operator_add, std::move(parameters)));
                            
                            case '-':
                                return exp_t(new OperatorExpression(block.position, optype::operator_subtract, std::move(parameters)));
                            
                            case '*':
                                return exp_t(new OperatorExpression(block.position, optype::operator_multiply, std::move(parameters)));
                            
                            case '/':
                                return exp_t(new OperatorExpression(block.position, optype::operator_divide, std::move(parameters)));
                            
                            case '<':
                                return exp_t(new OperatorExpression(block.position, operation == "<=" ? optype::operator_less_or_equal : optype::operator_less, std::move(parameters)));
                            
                            case '>':
                                return exp_t(new OperatorExpression(block.position, operation == ">=" ? optype::operator_greater_or_equal : optype::operator_greater, std::move(parameters)));
                            
                            case '&':
                                if(operation != "&&"){ throw InvalidExpression(block.position, "Not a valid operator [" + operation + "] (parse error)"); }
                                return exp_t(new OperatorExpression(block.position, optype::operator_and, std::move(parameters)));
                            
                            case '|':
                                if(operation != "||"){ throw InvalidExpression(block.position, "Not a valid operator [" + operation + "] (parse error)"); }
                                return exp_t(new OperatorExpression(block.position, optype::operator_or, std::move(parameters)));
                            
                            case '!':
                                return exp_t(new OperatorExpression(block.position, optype::operator_not, std::move(parameters)));
                        };

                        throw InvalidExpression(block.position, "Invalid operator (parse error) [" + operation + "]");
                    }

                    {
                        // the only pattern left is a function expression

                        if(block.view.size() < 2){
                            throw InvalidExpression(block.position, "Function expressions require at least one arguments");
                        }

                        std::list<Expression::expression_t> parameters;

                        for(auto it = ++block.view.begin(); it != block.view.end(); ++it){
                            parameters.push_back(std::holds_alternative<Token>(*it) ? atomic_expression_from_token(std::get<Token>(*it)) : read_block_into_expression(std::get<Block>(*it)));
                        }

                        Expression::expression_t function = std::holds_alternative<Token>(block.view.front()) ? atomic_expression_from_token(std::get<Token>(block.view.front())) : read_block_into_expression(std::get<Block>(block.view.front()));
                    
                        return exp_t(new FunctionExpression(block.position, function, std::move(parameters)));
                    }
                    
                    // unreachable
                    throw InvalidExpression(block.position, "Failed to match expression pattern (parse error)");
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
                 *  @desc calls read_block_into_expression
                 *  @return reference to stream 
                **/
                ExpressionStreamIterator& operator ++() noexcept(false) {
                    if(stream != end){
                        cursor = read_block_into_expression(*stream);
                        ++stream;
                    } else {
                        cursor = Expression::expression_t(nullptr);
                    }

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