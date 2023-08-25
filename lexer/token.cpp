#include "token.hpp"

#include <algorithm>    // used for std::all_of
#include <vector>       // used to create container from initializer list

#include <cctype>       // used for std::isdigit

/**
 *  Stand alone function definitions
**/

const char* to_string(TokenType type){
    const char* token_type_string_table[] = {
        "null",
        "end_of_file",
        "delimiter",
        "numeric",
        "keyword",
        "operation",
        "reference"
    };

    return token_type_string_table[(int)type];
}

/**
 *  Implimentation of structure Token
**/

Token Token::from_string(std::string value, TokenPosition position) noexcept(false) {
    // tests if a value is in a list
    const auto in_set = [](auto test, std::vector<decltype(test)> set) -> bool { return std::any_of(set.begin(), set.end(), [test](auto x) -> bool { return x == test; }); };
    
    if(value == ")" || value == "("){
        return Token(value, position, TokenType::delimiter);
    } else if(std::isdigit(value[0])) {
        if(std::all_of(value.begin(), value.end(), [](char value) -> bool { return std::isdigit(value); })){
            return Token(value, position, TokenType::numeric);
        }

        throw InvalidTokenString("Only numeric tokens can start with a numeric digit", position);
    } else if(in_set(value, {"define", "lambda", "if"})) {
        return Token(value, position, TokenType::keyword);
    } else if(in_set(value, {"+", "-", "*", "/", ">", "<", ">=", "<=", "print"})) {
        return Token(value, position, TokenType::operation);
    } else {
        return Token(value, position, TokenType::reference);
    }
}