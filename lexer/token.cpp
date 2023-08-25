#include "token.hpp"

/**
 *  Stand alone function definitions
**/
const char* to_string(TokenType type){
    const char* token_type_string_table[] = {
        "end_of_file",
        "null",
        "delimiter",
        "test"
    };

    return token_type_string_table[(int)type];
}

/**
 *  Implimentation of structure Token
**/

Token Token::from_string(std::string value, TokenPosition position){
    if(value == ")" || value == "("){
        return Token(value, position, TokenType::delimiter);
    } else {
        return Token(value, position, TokenType::test);
    }
}