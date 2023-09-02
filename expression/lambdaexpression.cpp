#include "lambdaexpression.h"

#include "../value/functionvalue.h"
#include "../value/notimplemented.hpp"

LambdaExpression::LambdaExpression(const Token::TokenPosition &position, std::list<std::string> parameters, expression_t body) : Expression(position), parameters(std::move(parameters)), body(std::move(body)) {}

Value::value_t LambdaExpression::operator ()(ProgramState &state) const {
    return Value::value_t(new FunctionValue([&state, *this](std::list<Value::value_t> parameters) -> Value::value_t {
        if(parameters.size() != this->parameters.size()){
            throw NotImplemented("Attempt to call function with incorrect number of parameters");
        }

        state.push();

        auto values = parameters.begin();

        auto names = this->parameters.begin();
        const auto end = this->parameters.end();

        while(names != end){
            state.set(*names, *values);
            ++names;
            ++values;
        }

        Value::value_t value = (*body)(state);

        state.pop();

        return value;
    }));
}