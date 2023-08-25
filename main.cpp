#include "lexer/lexstream.hpp"

#include <cstdio>

int main(){
    for(const Token& token : LexStream("test/example.fl")){
        std::printf("Token{(%ld, %ld), %s, %s}\n", token.position.line, token.position.index, token.value.c_str(), to_string(token.type));
    }
    return 0;
}