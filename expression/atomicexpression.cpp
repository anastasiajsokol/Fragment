#include "atomicexpression.h"

AtomicExpression::AtomicExpression(const Token::TokenPosition &position, Value::value_t value) : Expression(position), value(value) {}
AtomicExpression::AtomicExpression(const Token::TokenPosition &position, std::string value) : Expression(position), value(value) {}

Value::value_t AtomicExpression::operator ()(ProgramState& state) const {
    if(reference){
        return (*state.get(std::get<std::string>(value)))(state);
    }
    return std::get<Value::value_t>(value);
}