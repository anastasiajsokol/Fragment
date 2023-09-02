#include "lexstream.hpp"

#include "invalidlexeme.hpp"    // defines lexer::InvalidLexeme used to report error turning lexemes into tokens

#include <algorithm>            // defines std::all_of and std::any_of for pattern matching
#include <ios>                  // defines std::ios_base::failure which may be thrown by LexStream::LexStream()
#include <string>               // defines std::string and std::string_literals::operator ""s which are used to manage lexemes
#include <optional>             // defines std::optional which makes reading EOF token strings easier
#include <vector>               // defines std::vector used as a generic container to wrap initializer list with .begin() and .end() methods

#include <cctype>               // defines std::isspace and std::isdigit for pattern matching

using std::string_literals::operator ""s;
using namespace lexer;

/**
 *  Implimentation of class LexStream
**/

LexStream::LexStream(const char* const filepath) noexcept(false) : source(unique_file_ptr(std::fopen(filepath, "r"), std::fclose)) {
    // if std::fopen returned nullptr, report error and cancle construction
    if(!source){
        throw std::ios_base::failure("Unable to open file for reading: "s + filepath);
    }
}

LexStream::LexStreamIterator LexStream::begin() noexcept(false) {
    return LexStream::LexStreamIterator(std::move(source));
}

const Token LexStream::end() const noexcept {
    // sentenial token
    return Token("End of File", Token::TokenPosition{-1, -1}, Token::TokenType::end_of_file);
}

/**
 *  Implimentation of nested structure LexStream::LexStreamIterator
**/

LexStream::LexStreamIterator::LexStreamIterator(unique_file_ptr input) noexcept(false) : input(std::move(input)) {
    // check if input == nullptr
    if(!this->input){
        throw LexStreamDoubleReadException("Detected attempt to iterate over invalidated LexStream instance, instances are read once!");
    }

    // set cursor to first token
    ++*this;
}

std::pair<Token::TokenPosition, std::optional<std::string>> LexStream::LexStreamIterator::read_lexeme() noexcept {
    // peek ahead to next value
    const auto peek = [](std::FILE* stream) -> int { int value = getc(stream); ungetc(value, stream); return value; };

    // wrapper around getc that also updates position
    const auto read = [this](std::FILE* stream) -> int {
        const int value = getc(stream);
        if(value == '\n'){
            ++this->position.line;
            this->position.index = 0;
        } else {
            ++this->position.index;
        }
        return value;
    };

    // read next possible token (note: may be invalid!) from file
    const auto next = [peek, read](std::FILE* stream) -> std::optional<std::string> {
        // values that evaluate to true signify an end to reading
        const auto is_token_terminator = [](int character) -> bool { return (character == EOF) || !character || std::isspace(character) || (character == '(' || character == ')'); };

        // clear whitespace
        int ch = read(stream);
        while(ch != EOF && std::isspace(ch)){ ch = read(stream); }

        // signal end of file if applicable
        if(ch == EOF){
            return std::nullopt;
        }

        // read till terminator
        std::string sequence(1, ch);

        if(is_token_terminator(ch)){
            return sequence;
        }

        if(ch == '"'){
            do {
                sequence += ch = read(stream);
            } while(ch != '"' && ch != EOF);
        } else {
            while(!is_token_terminator(peek(stream))){
                sequence += ch = read(stream);
            }
        }

        return sequence;
    };

    // save start position
    const Token::TokenPosition start_position = position;

    // get lexeme
    const std::optional<std::string> lexeme = next(input.get());

    // return the combined pair
    return std::pair<Token::TokenPosition, std::optional<std::string>>(start_position, lexeme);
}

Token LexStream::LexStreamIterator::lexeme_to_token(const std::pair<Token::TokenPosition, std::optional<std::string>> &lexeme) noexcept(false) {
    // early exit if EOF lexeme
    if(!lexeme.second.has_value()){
        return Token("End of File", lexeme.first, Token::TokenType::end_of_file);
    }

    // easier to use
    const Token::TokenPosition position = lexeme.first;
    const std::string value = lexeme.second.value();

    // tests if a value is in a list
    const auto in_set = [value](std::vector<const char*> set) -> bool { return std::any_of(set.begin(), set.end(), [value](auto x) -> bool { return value == x; }); };
    
    if(in_set({"(", ")"})){
        return Token(value, position, Token::TokenType::delimiter);
    } else if(value[0] == '"'){
        if(value[value.length() - 1] != '"'){
            throw InvalidLexeme("Unclosed string, all string literals must end with a closing quotation mark", position);
        }

        return Token(value.substr(1, value.length() - 2), position, Token::TokenType::stringliteral);
    } else if(std::isdigit(value[0])) {
        // valid numeric tokens must be all numeric with optional decimal point
        int8_t allowed_decimals = 1;
        if(std::all_of(value.begin(), value.end(), [&allowed_decimals](char value) -> bool { return std::isdigit(value) || (value == '.' && !--allowed_decimals); })){
            return Token(value, position, Token::TokenType::numeric);
        }

        throw InvalidLexeme("Only numeric tokens can start with a numeric digit", position);
    } else if(in_set({"true", "false"})) {
        return Token(value, position, Token::TokenType::boolean);
    } else if(in_set({"define", "lambda", "if"})) {
        return Token(value, position, Token::TokenType::keyword);
    } else if(in_set({"+", "-", "*", "/", ">", "<", "=", ">=", "<="})) {
        return Token(value, position, Token::TokenType::operation);
    } else if(value == "%%") {
        return Token(value, position, Token::TokenType::comment);
    }  else {
        return Token(value, position, Token::TokenType::reference);
    }
}

LexStream::LexStreamIterator& LexStream::LexStreamIterator::operator ++() noexcept(false) {
    cursor = lexeme_to_token(read_lexeme());
    return *this;
}