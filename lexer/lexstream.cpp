#include "lexstream.hpp"

#include <ios>          // defines std::ios_base::failure which may be thrown by LexStream::LexStream()
#include <string>       // used for std::string and std::string_literals::operator ""s;
#include <optional>     // used for std::optional which makes reading EOF token strings easier

#include <cctype>       // used for std::isspace

using std::string_literals::operator ""s;

/**
 *  Implimentation of class LexStream
**/

LexStream::LexStream(zstring const filepath) noexcept(false) : source(unique_file_ptr(std::fopen(filepath, "r"), std::fclose)) {
    // if std::fopen returned nullptr, report error and cancle construction
    if(!source){
        throw std::ios_base::failure("Unable to open file for reading: "s + filepath);
    }
}

LexStream::LexStreamIterator LexStream::begin() noexcept(false) {
    return LexStream::LexStreamIterator(std::move(source));
}

Token LexStream::end() const noexcept {
    // sentenial token
    return Token{TokenPosition{-1, -1}, "End of File", TokenType::end_of_file};
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

LexStream::LexStreamIterator& LexStream::LexStreamIterator::operator ++() noexcept {
    // peek ahead to next value
    const auto peek = [](std::FILE* stream) -> int { int value = getc(stream); ungetc(value, stream); return value; };

    // wrapper around getc that also updates position
    const auto read = [this](std::FILE* stream) -> int {
        int value = getc(stream);
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

        while(!is_token_terminator(peek(stream))){
            sequence += ch = read(stream);
        }

        return sequence;
    };

    // copy start of token (reporting start position over end is just slightly cleaner in my opinion)
    TokenPosition start_position = position;
    
    // return token, or return sentenial to signal end of file
    std::optional<std::string> token = next(input.get());
    cursor = token.has_value() ? Token{start_position, token.value(), TokenType::test} : Token{position, "End of File", TokenType::end_of_file};
    
    // really, here either classify token or have a Token::from_string(std::string, TokenPosition position) function

    return *this;
}