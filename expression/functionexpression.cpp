#include "functionexpression.h"

#include "invalidexpression.hpp"    // defines InvalidExpression exception

FunctionExpression::FunctionExpression(const Token::TokenPosition &position, Expression::expression_t function, std::list<Expression::expression_t> arguments) : Expression(position), function(function), arguments(std::move(arguments)) {
    if(!this->arguments.size()){
        throw InvalidExpression(position, "Function expressions require at least one argument (may be a parser error, see 'self expression')");
    }
}

Value::value_t FunctionExpression::operator ()(ProgramState& state) const {
    Value::value_t f = (*function)(state);

    if(f->type != ValueType::function){
        throw InvalidExpression(position, "Expected function at start of function expression, got " + to_string(f->type));
    }

    std::list<Value::value_t> values;

    for(auto &argument : arguments){
        values.push_back((*argument)(state));
    }
    
    return (std::get<std::function<Value::value_t(std::list<Value::value_t>)>>(f->value))(values);
}