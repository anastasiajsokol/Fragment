#include "operatorexpression.h"

#include "invalidexpression.hpp"    // defines InvalidExpression which can be thrown if an attempt to construct a non-sensical expression is made
#include <functional>               // defines std::function used 

OperatorExpression::OperatorExpression(const Token::TokenPosition &position, const OperatorExpression::OperatorType type, const std::list<Expression> arguments) : Expression(position), type(type), arguments(arguments) {
    if(arguments.size() == 0){
        throw InvalidExpression(position, "Operator expressions require at least one argument");
    }
}

Value OperatorExpression::operator ()(){
    std::function<Value(const Value&, const Value&)> operators[] = {
        [](const Value &a, const Value &b) -> Value { return a + b; }
    };
}