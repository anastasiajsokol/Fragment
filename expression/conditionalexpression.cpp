#include "conditionalexpression.h"

ConditionalExpression::ConditionalExpression(const Token::TokenPosition &position, Expression::expression_t condition, Expression::expression_t truthy, Expression::expression_t falsy) : Expression(position), condition(std::move(condition)), truthy(std::move(truthy)), falsy(std::move(falsy)) {}

Value::value_t ConditionalExpression::operator ()(ProgramState& state) const {
    if((bool)((*condition)(state))){
        return (*truthy)(state);
    } else {
        return (*falsy)(state);
    }
}