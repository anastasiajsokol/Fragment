#include "lexer/invalidlexeme.hpp"
#include "lexer/lexstream.hpp"
#include "parser/blockstream.hpp"
#include "parser/invalidblock.hpp"

#include <cstdio>

int main(){
    const char* filepath = "test/example_factorial.fl";

    try {
        for(const Block& block : parser::BlockStream(lexer::LexStream(filepath))){
            std::printf("Block with size: %ld\n", block.size());
        }
    } catch(std::ios_base::failure error){
        std::printf("File Error\n\t%s\n", error.what());
    } catch(lexer::InvalidLexeme error) {
        std::printf("Invalid Lexeme Exception\n\terror: %s\n\tposition: (%ld, %ld) in file %s\n", error.what(), error.position.line, error.position.index, filepath);
    } catch(parser::InvalidBlock error) {
        std::printf("Invalid Block Exception\n\terror: %s\n\tposition: (%ld, %ld) in file %s\n", error.what(), error.position.line, error.position.index, filepath);
    }

    return 0;
}