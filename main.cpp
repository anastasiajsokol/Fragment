#include "lexer/lexstream.hpp"
#include "parser/blockstream.hpp"

#include <cstdio>

int main(){
    const char* filepath = "test/example_factorial.fl";

    try {
        for(const Block& block : parser::BlockStream(lexer::LexStream(filepath))){
            std::printf("Block with size: %ld\n", block.size());
        }
    } catch(parser::InvalidBlock error) {
        std::printf("Invalid Block Exception\n\terror: %s\n\tposition: (%ld, %ld) in file %s\n", error.what(), error.position.line, error.position.index, filepath);
    }

    return 0;
}