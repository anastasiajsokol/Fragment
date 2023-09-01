/**
 *      @file main.cpp
 *      @brief defines entry point for generic use
 *      @author Anastasia Sokol
 *      @copyright 2023 Anastasia Sokol | Released under The Unlicense
 * 
 *      <a href="https://github.com/anastasiajsokol/FragmentLisp">Github Repository</a> 
**/

#include "lexer/invalidlexeme.hpp"      // defines lexer::InvalidLexeme for reporting generic lexing errors
#include "lexer/lexstream.hpp"          // defines lexer::LexStream for creating token streams from file path
#include "parser/blockstream.hpp"       // defines parser::BlockStream for creating block streams from token streams
#include "parser/invalidblock.hpp"      // defines parser::InvalidBlock for reporting generic block parsing errors
#include "parser/expressionstream.hpp"  // defines parser::ExpressionStream for turning creating an expression stream from block streams

#include <ios>                      // defines std::ios_base::failure for file io errors (also defined in lexer/lexstream.hpp but that is not generally guaranteed)

#include <cstdio>                   // defines std::fprintf, stderr, EXIT_FAILURE, and EXIT_SUCCESS for reporting program execution state

int main(){
    const char* filepath = "examples/factorial.fl";

    try {
        for(const auto& expression : parser::ExpressionStream(parser::BlockStream(lexer::LexStream(filepath)))){
            std::printf("Expression of at: (%ld, %ld)\n", expression->position.line, expression->position.index);
        }
    } catch(std::ios_base::failure error){
        std::fprintf(stderr, "File Error\n\t%s\n", error.what());
        return EXIT_FAILURE;
    } catch(lexer::InvalidLexeme error) {
        std::fprintf(stderr, "Invalid Lexeme Exception\n\terror: %s\n\tposition: (%ld, %ld) in file %s\n", error.what(), error.position.line, error.position.index, filepath);
        return EXIT_FAILURE;
    } catch(parser::InvalidBlock error) {
        std::fprintf(stderr, "Invalid Block Exception\n\terror: %s\n\tposition: (%ld, %ld) in file %s\n", error.what(), error.position.line, error.position.index, filepath);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}