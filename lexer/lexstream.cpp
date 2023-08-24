#include "lexstream.h"

#include <ios>
#include <string>

#include <cstdio>

using std::string_literals::operator ""s;

LexStream::LexStream(const char* filepath) throw(std::ios_base::failure) {
    source = std::fopen(filepath, "r");

    if(source == nullptr){
        throw std::ios_base::failure("Unable to open file for reading: "s + filepath);
    }
}

struct LexStream::LexStreamIterator {
        using iterator_category = std::input_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = Token;
        using pointer           = value_type*;
        using reference         = value_type&;
    };