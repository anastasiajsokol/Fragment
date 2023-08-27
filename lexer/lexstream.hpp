/**
 *      @file lexer/lexstream.hpp
 *      @brief defines LexStream class to convert file path into stream of Tokens
 *      @author Anastasia Sokol
 * 
 *      LexStream is implimented as a std::input_iterator, meaning it can only be iterated over once and is readonly
 *      to check if the stream is still valid (ie, unread) you can use bool LexStream::is_still_valid() or use the LexStream::operator bool() conversion
 *      extended .hpp due to limited use of inline functions
**/

#ifndef LEXER_LEXSTREAM_H
#define LEXER_LEXSTREAM_H

#include "../datatype/token.hpp"    // defines structure Token and enum class TokenType

#include <iterator>                 // defines std::input_iterator_tag used to tag LexStream::LexStreamIterator as input iterator
#include <memory>                   // defines std::unique_ptr used to manage std::FILE* ownership
#include <stdexcept>                // defines std::runtime_error used for LexStreamDoubleReadException
#include <string>                   // defines std::string used for lexemes
#include <utility>                  // defines std::pair used for pairing position and lexeme data
#include <optional>                 // defines std::optional used to manage a failure to read a lexeme due to EOF condition

#include <cstdio>                   // defines std::FILE used to provide complete control over reading from input file

namespace lexer {

typedef std::unique_ptr<std::FILE, int(*)(std::FILE*)> unique_file_ptr;     // used to represent std::FILE* as a std::unqiue_ptr

/**
 *  @brief represents language input file, read only and read once, designed to be used in ranged for loop
 * 
 *  designed to be used as a c++ standard container for reading tokens from input file
 *  read only, read once - meaning that you are not supposed to write to the container, and can only iterate over an instance ONCE
 *  can not be copied !! if you need a second copy (for some reason, probably doing something wrong) then create a completely new instance
 *  however, the class can be moved using std::move
**/
class LexStream {
    private:
        unique_file_ptr source; // represent file, ownership passed to iterator and *never returned* - makes class read once

    public:
        /**
         *  @brief exception raised if an attempt is made to iterate over LexStream a second time
         * 
         *  any LexStream instance is invalidated after being iterated over, so attempting to read twice will result in a LexStreamDoubleReadException
         *  this exception is simply an extension, nearly an alias, of std::runtime_error
        **/
        struct LexStreamDoubleReadException : public std::runtime_error {
            /**
             *  @brief simply passes along const std::string& to std::runtime_error
            **/
            inline LexStreamDoubleReadException(const std::string& message) noexcept : std::runtime_error(message) {}
        };
        
        /**
         *  @brief read only, read once iterator for LexStream - returns tokens
         * 
         *  iterates over file, returning tokens as it goes
         *  uses sentenial value for end comparison (specifically, a token with type TokenType::end_of_file)
        **/
        struct LexStreamIterator {
            private:
                unique_file_ptr input;          // represents file, has full ownership
                Token::TokenPosition position;  // used to keep track of position in file
                Token cursor;                   // used to store last token read

                /**
                 *  @brief read next lexeme
                 *  @desc attempts to read a lexeme from input, if EOF returns std::nullopt, updates position to end of lexeme and returns start of lexeme
                 *  @return a pair containing the starting position of the lexeme, and the lexeme as a string if one was there (std::nullopt if EOF)
                **/
                std::pair<Token::TokenPosition, std::optional<std::string>> read_lexeme() noexcept;

                /**
                 *  @brief convert a Token::TokenPosition, std::string pair into a token
                 *  @desc attempts to convert an optional pair into a token, if std::nullopt returns end_of_file token
                 *  @throws InvalidLexeme if the lexeme passed is an std::string without a valid lexeme representation
                 *  @return Token value that the lexeme represented
                **/
                static Token lexeme_to_token(const std::pair<Token::TokenPosition, std::optional<std::string>>&) noexcept(false);

            public:
                using iterator_category = std::input_iterator_tag;
                using difference_type   = void;
                using value_type        = Token;
                using pointer           = value_type*;
                using reference         = value_type&;

                /**
                 *  @brief construct LexStreamIterator, should only be used by LexStream::begin()
                 *  @desc create iterator for tokens in file input, calls LexStreamDoubleReadException if input is a nullptr
                 *  @param input input file to iterate over, claims ownership (must be std::move'd)
                 *  @throws LexStreamDoubleReadException if input is nullptr
                **/
                LexStreamIterator(unique_file_ptr input) noexcept(false);
                
                /**
                 *  @brief read next token from file
                 *  @desc attempts to read the next token from input file, if at end of file does nothing, invalidates past references and pointers
                 *  @throws InvalidLexeme from internal call to lexeme_to_token
                 *  @return reference to LexStreamIterator
                **/
                LexStreamIterator& operator ++() noexcept(false);
                
                /**
                 *  @brief get a const pointer to current token
                 *  @desc this value is read only due to the nature of the input iterator
                 *  @return pointer to cursor token
                **/
                inline const Token* operator ->() const noexcept {
                    return &cursor;
                }
                
                /**
                 *  @brief get a const pointer to current token
                 *  @desc this value is read only due to the nature of the input iterator
                 *  @return reference to cursor token
                **/
                inline const Token& operator *() const noexcept {
                    return cursor;
                }
                
                /**
                 *  @brief used to compare to sentenial token value
                 *  @desc checks if type of passed Token is the same as the current token
                 *  @param token token to compare types to, should really only be the sentenial token returned by LexStream::end()
                 *  @return bool representing whether the types of the passed token and the cursor token are equal
                **/
                inline bool operator ==(const Token& token) const noexcept {
                    return token.type == cursor.type;
                }

                /**
                 *  @brief used to compare to sentenial token value
                 *  @desc checks if type of passed Token is not the same as the current token
                 *  @param token token to compare types to, should really only be the sentenial token returned by LexStream::end()
                 *  @return bool representing whether the types of the passed token and the cursor token are not equal
                **/
                inline bool operator !=(const Token& token) const noexcept {
                    return token.type != cursor.type;
                }
        };
        
        /**
         *  @brief create a LexStream from the file located at filepath
         *  @desc creates LexStream from c string filepath, if unable to open file for reading will throw a std::ios_base_failure exception
         *  @param filepath null terminated c-style string with filepath to input file
         *  @throws std::ios_base::failure from <ios>
        **/
        LexStream(const char* const filepath) noexcept(false);
        
        /**
         *  @brief create LexStreamIterator to start of LexStream
         *  @desc iterator over tokens in LexStream file, only one can be called once for LexStream instance, should not be called directly
         *  @throws LexStreamDoubleReadException from LexStreamIterator or InvalidLexeme from operator ++()
         *  @return a LexStreamIterator which can be used to iterate over tokens in file 
        **/
        LexStreamIterator begin() noexcept(false);

        /**
         *  @brief get end of file sentenial token
         *  @desc used to allow for ranged for loop, which is how the LexStream class is designed to be used
         *  @return token representing the end of the file, used as symbollic end for LexStreamIterator
        **/
        Token end() const noexcept;

        /**
         *  @brief check if LexStream instance is still valid
         *  @desc it is impossible to construct an invalid LexStream, however by reading the iterator (calling LexStream::begin()) the instance is invalidated
         *  @return bool representing if LexStream instance is still valid (has not yet been consumed)
        **/
        inline bool is_still_valid() const noexcept {
            return (bool)source;
        }

        /**
         *  @brief same as LexStream::is_still_valid() | check if LexStream instance is still valid
         *  @return bool representing if LexStream instance is still valid (has not yet been consumed)
        **/
        inline operator bool() const noexcept {
            return (bool)source;
        }
};

}; // end of namespace lexer

#endif