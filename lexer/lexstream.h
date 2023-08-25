/**
 *      @file lexer/lexstream.h
 *      @brief defines LexStream class to convert file path into stream of Tokens
 *      @author Anastasia Sokol
 * 
 *      LexStream is implimented as a std::input_iterator, meaning it can only be iterated over once
 *      to check if the stream is still valid (ie, unread) you can use bool LexStream::is_still_valid() or use the LexStream::operator bool() conversion
**/

#ifndef LEXER_LEXSTREAM_H
#define LEXER_LEXSTREAM_H

#include "token.h"

#include <iterator>
#include <ios>
#include <memory>

typedef std::unique_ptr<std::FILE, int(*)(FILE*)> unique_file_ptr;  // used to represent std::FILE* as a std::unqiue_ptr
typedef const char* zstring;                                        // used to represent null terminated c style string (refer to c++ core guidlines for why)

class LexStream {
    private:
        unique_file_ptr source;
        zstring filepath;

    public:
        struct LexStreamDoubleReadException : public std::runtime_error {
            LexStreamDoubleReadException(const std::string&);
        };

        struct LexStreamIterator {
            private:
                unique_file_ptr input;

            public:
                using iterator_category = std::input_iterator_tag;
                using difference_type   = std::ptrdiff_t;
                using value_type        = Token;
                using pointer           = value_type*;
                using reference         = value_type&;

                LexStreamIterator(unique_file_ptr input) throw(LexStreamDoubleReadException);
                
                LexStreamIterator& operator ++() noexcept;
                
                const Token *operator ->();
                const Token *operator *();
                
                bool operator ==(const Token&) const noexcept;
                bool operator !=(const Token&) const noexcept;
        };
        
        LexStream(zstring const filepath) throw(std::ios_base::failure);
        
        LexStreamIterator begin() throw(LexStreamDoubleReadException);
        Token end() const;

        bool is_still_valid() const;
        operator bool() const;
};

#endif