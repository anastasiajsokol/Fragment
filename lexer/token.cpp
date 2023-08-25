#include "token.hpp"

#include <algorithm>    // used for std::all_of
#include <vector>       // used to create container from initializer list

#include <cctype>       // used for std::isdigit

/**
 *  Stand alone function definitions
**/

std::string to_string(const Token::TokenType type){
    // lookup table corresponding to int representation of Token::TokenType enum
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

Token Token::from_string(const std::string& value, const TokenPosition& position) noexcept(false) {
    // tests if a value is in a list
    const auto in_set = [value](std::vector<const char*> set) -> bool { return std::any_of(set.begin(), set.end(), [value](auto x) -> bool { return value == x; }); };
    
    if(in_set({"(", ")"})){
        return Token(value, position, TokenType::delimiter);
    } else if(std::isdigit(value[0])) {
        // valid numeric tokens must be all numeric
        if(std::all_of(value.begin(), value.end(), [](char value) -> bool { return std::isdigit(value); })){
            return Token(value, position, TokenType::numeric);
        }

        throw InvalidTokenString("Only numeric tokens can start with a numeric digit", position);
    } else if(in_set({"define", "lambda", "if"})) {
        return Token(value, position, TokenType::keyword);
    } else if(in_set({"+", "-", "*", "/", ">", "<", "=", ">=", "<=", "print"})) {
        return Token(value, position, TokenType::operation);
    } else {
        return Token(value, position, TokenType::reference);
    }
}