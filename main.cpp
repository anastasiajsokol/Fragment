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
#include <cstring>                  // defines std::strcmp

int main(int argc, char **argv){
    // command interface
    if(argc != 2){
        std::puts("The Fragment Interpeter requires exactly one parameters\n\tallowed: -v, --version, -h, --help, or a path to the input file");
        return EXIT_FAILURE;
    }

    if(!std::strcmp(argv[1], "-v") || !std::strcmp(argv[1], "--version")){
        std::puts("Fragment Interpeter v. 1.0");
        return EXIT_SUCCESS;
    } else if(!std::strcmp(argv[1], "-h") || !std::strcmp(argv[1], "--help")){
        std::puts("Fragment Interpeter v. 1.0\n\tallowed parameters: -v, --version, -h, --help, or an input file path\n\tunfortunately no documentation is currently available");
        return EXIT_SUCCESS;
    }
    
    // interpeter interface
    const char* filepath = argv[1];

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