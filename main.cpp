#include "lexer/lexstream.hpp"

#include <cstdio>

int main(){
    for(const Token& token : LexStream("test/example_factorial.fl")){
        std::printf("Token{(%ld, %ld), %s, %s}\n", token.position.line, token.position.index, token.value.c_str(), to_string(token.type).c_str());
    }
    return 0;
}