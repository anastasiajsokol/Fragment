#include "defineexpression.h"

DefineExpression::DefineExpression(const Token::TokenPosition& position, const std::string& name, expression_t value) : Expression(position), name(name), value(std::move(value)) {}

Value::value_t DefineExpression::operator ()(ProgramState& state) const {
    return state.set(name, (*value)(state));
}