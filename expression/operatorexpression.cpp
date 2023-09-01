#include "operatorexpression.h"

#include "invalidexpression.hpp"    // defines InvalidExpression for reporting errors

OperatorExpression::OperatorExpression(const Token::TokenPosition& position, OperatorType type, std::list<Expression::expression_t> arguments) : Expression(position), type(type), arguments(std::move(arguments)) {
    if(!this->arguments.size()){
        throw InvalidExpression(position, "All operators require at least one arguments");
    } else if(type == OperatorExpression::OperatorType::operator_not && this->arguments.size() != 1){
        throw InvalidExpression(position, "Negation is only defined for a single value");
    }
}

Value::value_t OperatorExpression::operator ()(ProgramState& state) const {
    using optype = OperatorExpression::OperatorType;
    using value_t = Value::value_t;

    if(type == optype::operator_not){
        // ensured that only one argument, special case
        return !(*arguments.front())(state);
    }

    // similar to std::accumulate, but specialized for this
    const auto accumulate = [&state](auto start, const auto end, auto op) -> value_t {
        value_t base = (**start)(state);
        for(++start; start != end; ++start){
            base = op(base, (**start)(state));
        }
        return base;
    };

    // safe to assume that all operators have at least one argument, and that not has only one
    switch(type){
        case optype::operator_add:
            return accumulate(arguments.begin(), arguments.end(), [](auto a, auto b){ return a + b; });
        
        case optype::operator_subtract:
            return accumulate(arguments.begin(), arguments.end(), [](auto a, auto b){ return a - b; });
        
        case optype::operator_multiply:
            return accumulate(arguments.begin(), arguments.end(), [](auto a, auto b){ return a * b; });
        
        case optype::operator_divide:
            return accumulate(arguments.begin(), arguments.end(), [](auto a, auto b){ return a / b; });
        
        case optype::operator_less:
            return accumulate(arguments.begin(), arguments.end(), [](auto a, auto b){ return a < b; });
        
        case optype::operator_greater:
            return accumulate(arguments.begin(), arguments.end(), [](auto a, auto b){ return a > b; });
        
        case optype::operator_less_or_equal:
            return accumulate(arguments.begin(), arguments.end(), [](auto a, auto b){ return a <= b; });
        
        case optype::operator_greater_or_equal:
            return accumulate(arguments.begin(), arguments.end(), [](auto a, auto b){ return a >= b; });
        
        case optype::operator_and:
            return accumulate(arguments.begin(), arguments.end(), [](auto a, auto b){ return a && b; });
        
        case optype::operator_or:
            return accumulate(arguments.begin(), arguments.end(), [](auto a, auto b){ return a || b; });
    }

    throw InvalidExpression(position, "Invalid Operator (possibly a parsing error)");
}