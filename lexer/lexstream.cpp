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
    if(!source){
        throw std::ios_base::failure("Unable to open file for reading: "s + filepath);
    }
}

LexStream::LexStreamIterator LexStream::begin() noexcept(false) {
    return LexStream::LexStreamIterator(std::move(source));
}

Token LexStream::end() const noexcept {
    return Token{TokenPosition{-1, -1}, "End of File", TokenType::end_of_file};
}

/**
 *  Implimentation of nested structure LexStream::LexStreamIterator
**/

LexStream::LexStreamIterator::LexStreamIterator(unique_file_ptr input) noexcept(false) : input(std::move(input)) {
    if(!this->input){
        throw LexStreamDoubleReadException("Detected attempt to iterate over invalidated LexStream instance, instances are read once!");
    }
}

LexStream::LexStreamIterator& LexStream::LexStreamIterator::operator ++() noexcept {
    // read next possible token (note: may be invalid!) from file
    const auto next = [](std::FILE* stream) -> std::optional<std::string> {
        // values that evaluate to true signify an end to reading
        const auto is_token_terminator = [](int character) -> bool { return (character == EOF) || std::isspace(character) || (character == '(' || character == ')'); };

        // clear whitespace
        int ch = getc(stream);
        while(ch != EOF && std::isspace(ch)){ ch = getc(stream); }
        ungetc(ch, stream);

        if(ch == EOF){
            return std::nullopt;
        }

        // read till terminator
        std::string sequence(1, ch);

        while(!is_token_terminator(ch)){
            sequence += ch = getc(stream);
        }

        return sequence;
    };

    std::optional<std::string> token = next(input.get());
    cursor = token.has_value() ? Token{position, token.value(), TokenType::test} : Token{position, "End of File", TokenType::end_of_file};
    return *this;
}