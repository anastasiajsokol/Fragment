/**
 *      @file lexer/lexstream.hpp
 *      @brief defines LexStream class to convert file path into stream of Tokens
 *      @author Anastasia Sokol
 * 
 *      LexStream is implimented as a std::input_iterator, meaning it can only be iterated over once
 *      to check if the stream is still valid (ie, unread) you can use bool LexStream::is_still_valid() or use the LexStream::operator bool() conversion
 *      extended .hpp due to limited use of inline functions
**/

#ifndef LEXER_LEXSTREAM_H
#define LEXER_LEXSTREAM_H

#include "token.h"  // defines structure Token and enum class TokenType

#include <iterator> // used for std::input_iterator_tag, used to tag LexStream::LexStreamIterator as input iterator
#include <ios>      // defines std::ios_base::failure which may be thrown by LexStream::LexStream()
#include <memory>   // used to create alias unique_file_ptr which is used to manage std::FILE* ownership

#include <cstdio>   // defines std::FILE, while ifstream could have been used, by combining with unique_ptr we get move ownership for free

typedef std::unique_ptr<std::FILE, int(*)(std::FILE*)> unique_file_ptr;     // used to represent std::FILE* as a std::unqiue_ptr
typedef const char* zstring;                                                // used to represent null terminated c style string (refer to c++ core guidlines for why)

/**
 *  @brief represents language input file, read only and read once, designed to be used in ranged for loop
 * 
 *  designed to be used as a c++ standard container for reading tokens from input file
 *  read only, read once - meaning that you are not supposed to write to the container, and can only iterate over an instance ONCE
 *  can not be copied !! if you need a second copy (for some reason, probably doing something wrong) then create a completely new instance
 *  however, the class can be moved using std::move, though you may be using it wrong if that is something you need to do
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
            LexStreamDoubleReadException(const std::string& message) : std::runtime_error(message) {}
        };

        /**
         *  @brief read only, read once iterator for LexStream - returns tokens
         * 
         *  iterates over file, returning tokens as it goes
         *  uses sentenial value for end comparison (specifically, a token with type TokenType::end_of_file)
        **/
        struct LexStreamIterator {
            private:
                unique_file_ptr input;  // represents file, has full ownership
                Token cursor;           // used to store last token read

            public:
                using iterator_category = std::input_iterator_tag;
                using difference_type   = std::ptrdiff_t;
                using value_type        = Token;
                using pointer           = value_type*;
                using reference         = value_type&;

                /**
                 *  @brief construct LexStreamIterator, should only be used by LexStream::begin()
                 *  @desc create iterator for tokens in file input, calls LexStreamDoubleReadException if input is a nullptr
                 *  @param input input file to iterate over, claims ownership (must be std::move'd)
                **/
                LexStreamIterator(unique_file_ptr input) throw(LexStreamDoubleReadException);
                
                /**
                 *  @brief read next token from file
                 *  @desc attempts to read the next token from input file, if at end of file does nothing, invalidates past references and pointers
                **/
                LexStreamIterator& operator ++() noexcept;
                
                /**
                 *  @brief get a const pointer to current token
                 *  @desc this value is read only due to the nature of the input iterator
                **/
                inline const Token* operator ->() noexcept {
                    return &cursor;
                }
                
                /**
                 *  @brief get a const pointer to current token
                 *  @desc this value is read only due to the nature of the input iterator
                **/
                inline const Token* operator *() noexcept {
                    return &cursor;
                }
                
                /**
                 *  @brief used to compare to sentenial token value
                 *  @desc checks if type of passed Token is the same as the current token
                 *  @param token token to compare types to, should really only be the sentenial token returned by LexStream::end()
                **/
                inline bool operator ==(const Token& token) const noexcept {
                    return token.type == cursor.type;
                }

                /**
                 *  @brief used to compare to sentenial token value
                 *  @desc checks if type of passed Token is not the same as the current token
                 *  @param token token to compare types to, should really only be the sentenial token returned by LexStream::end()
                **/
                bool operator !=(const Token& token) const noexcept {
                    return token.type != cursor.type;
                }
        };
        
        /**
         *  @brief create a LexStream from the file located at filepath
         *  @desc creates LexStream from zstring path filepath, if unable to open file for reading will throw a std::ios_base_failure exception
         *  @param filepath null terminated c-style string with filepath to input file
        **/
        LexStream(zstring const filepath) throw(std::ios_base::failure);
        
        /**
         *  @brief create LexStreamIterator to start of LexStream
         *  @desc used to iterator over tokens in LexStream file, only one can be called once for LexStream instance, should not be called directly
        **/
        LexStreamIterator begin() throw(LexStreamDoubleReadException);

        /**
         *  @brief get end of file sentenial token
         *  @desc used to allow for ranged for loop, which is how the LexStream class is designed to be used
        **/
        Token end() const noexcept;

        /**
         *  @brief check if LexStream instance is still valid
         *  @desc it is impossible to construct an invalid LexStream, however by reading the iterator (calling LexStream::begin()) the instance is invalidated
        **/
        inline bool is_still_valid() const noexcept {
            return (bool)source;
        }

        /**
         *  @brief same as LexStream::is_still_valid() | check if LexStream instance is still valid
        **/
        inline operator bool() const noexcept {
            return (bool)source;
        }
};

#endif