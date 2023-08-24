#ifndef LEXER_LEXSTREAM_H
#define LEXER_LEXSTREAM_H

#include "token.h"

#include <iterator>
#include <ios>

class LexStream {
    private:
        std::FILE *source;

    public:
        struct LexStreamIterator;

        LexStream(const char* filepath) throw(std::ios_base::failure);
        
        Token next();
};

#endif