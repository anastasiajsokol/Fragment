#include "lexer/lexstream.hpp"

#include <cstdio>

int main(){
    LexStream stream("test/example.fl");
    for(const Token& token : stream){
        std::printf("Token{(%d, %d), %s, test}\n", token.position.line, token.position.index, token.value.c_str());
    }
    return 0;
}