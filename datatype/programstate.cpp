#include "programstate.h"

#include "invalidstate.hpp"

ProgramState::ProgramState(){
    this->push();
}

void ProgramState::push(){
    scope.push_back(std::unordered_map<std::string, Value::value_t>());
}

void ProgramState::pop(){
    scope.pop_back();
}

Value::value_t ProgramState::set(const std::string &name, Value::value_t value){
    (scope.back())[name] = value;
    return value;
}

Value::value_t ProgramState::get(const std::string &name) const {
    for (auto it = scope.rbegin(); it != scope.rend(); ++it){
        auto location = it->find(name);
        if(location == it->end()){
            return location->second;
        }
    }

    throw InvalidState("Unable to find a reference with name [" + name + "] in any scope");
}