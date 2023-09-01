#include "selfexpression.h"

SelfExpression::SelfExpression(const Token::TokenPosition &position, Expression::expression_t value) : Expression(position), value(std::move(value)) {}

Value::value_t SelfExpression::operator ()(ProgramState& state) const {
    Value::value_t unknown = (*value)(state);

    if(unknown->type == ValueType::function){
        // if function, attempt to evaluate without arguments
        return (std::get<std::function<Value::value_t(std::list<Value::value_t>)>>(unknown->value))(std::list<Value::value_t>());
    }

    return unknown;
}