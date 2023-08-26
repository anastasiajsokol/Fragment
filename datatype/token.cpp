#include "token.hpp"

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
        "reference",
        "stringliteral",
        "boolean"
    };

    return token_type_string_table[(int)type];
}
