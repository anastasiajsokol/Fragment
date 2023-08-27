#include "lexer/lexstream.hpp"
#include "parser/blockstream.hpp"

#include <cstdio>

int main(){
    for(const Block& token : parser::BlockStream(lexer::LexStream("test/example_factorial.fl"))){
        std::puts("yippee");    
    }

    return 0;
}