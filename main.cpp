/**
 *      @file main.cpp
 *      @brief defines entry point for generic use
 *      @author Anastasia Sokol
 *      @copyright 2023 Anastasia Sokol | Released under The Unlicense
 * 
 *      <a href="https://github.com/anastasiajsokol/Fragment">Github Repository</a> 
**/

#include "lexer/invalidlexeme.hpp"      // defines lexer::InvalidLexeme for reporting generic lexing errors
#include "lexer/lexstream.hpp"          // defines lexer::LexStream for creating token streams from file path
#include "parser/blockstream.hpp"       // defines parser::BlockStream for creating block streams from token streams
#include "parser/invalidblock.hpp"      // defines parser::InvalidBlock for reporting generic block parsing errors
#include "parser/expressionstream.hpp"  // defines parser::ExpressionStream for turning creating an expression stream from block streams
#include "datatype/invalidstate.hpp"    // defines InvalidState exception
#include "utility/standardlibrary.h"    // defines interface for standard library functions
#include "value/functionvalue.h"        // define FunctionValue for wrapping standard library functions
#include "value/notimplemented.hpp"     // defines NotImplemented exception

#include <ios>                          // defines std::ios_base::failure for file io errors (also defined in lexer/lexstream.hpp but that is not generally guaranteed)

#include <cstdio>                       // defines std::fprintf, stderr, EXIT_FAILURE, and EXIT_SUCCESS for reporting program execution state
#include <cstring>                      // defines std::strcmp

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
        std::puts("Fragment Interpeter v. 1.0\n\tallowed parameters: -v, --version, -h, --help, or an input file path\n\tsee README.md for more information");
        return EXIT_SUCCESS;
    }
    
    // interpeter interface
    const char* filepath = argv[1];

    try {
        // setup program state
        ProgramState state;

        state.set("print", Value::value_t(new FunctionValue(flstd::print)));
        state.set("println", Value::value_t(new FunctionValue(flstd::println)));
        state.set("readline", Value::value_t(new FunctionValue(flstd::readline)));
        state.set("readnumeric", Value::value_t(new FunctionValue(flstd::readnumeric)));
        
        // build and run program
        for(const auto& expression : parser::ExpressionStream(parser::BlockStream(lexer::LexStream(filepath)))){
            (*expression)(state);
        }
    } catch(std::ios_base::failure &error){
        std::fprintf(stderr, "\033[31mFile Error\033[39m\n\t%s\n", error.what());
        return EXIT_FAILURE;
    } catch(lexer::InvalidLexeme &error) {
        std::fprintf(stderr, "\033[31mInvalid Lexeme Exception\033[39m\n\terror: %s\n\tposition: (%ld, %ld) in file %s\n", error.what(), error.position.line, error.position.index, filepath);
        return EXIT_FAILURE;
    } catch(parser::InvalidBlock &error) {
        std::fprintf(stderr, "\033[31mInvalid Block Exception\033[39m\n\terror: %s\n\tposition: (%ld, %ld) in file %s\n", error.what(), error.position.line, error.position.index, filepath);
        return EXIT_FAILURE;
    } catch(InvalidExpression &error){
        std::fprintf(stderr, "\033[31mInvalid Expression\033[39m\n\terror: %s\n\tposition: (%ld, %ld) in file %s\n", error.what(), error.position.line, error.position.index, filepath);
    } catch(InvalidState &error){
        std::fprintf(stderr, "\033[31mInvalid Program State\033[39m\n\terror: %s\n\tposition: file %s\n", error.what(), filepath);
    } catch(NotImplemented &error){
        std::fprintf(stderr, "\033[31mOperation Not Implemented\033[39m\n\terror: %s\n\tposition: file %s\n", error.what(), filepath);
    }

    return EXIT_SUCCESS;
}