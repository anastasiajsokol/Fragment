/**
 *      @file parser/blockstream.h
 *      @brief defines LexStream class to convert a token stream into a stream of block objects
 *      @author Anastasia Sokol
**/

#ifndef PARSER_BLOCKSTREAM_H
#define PARSER_BLOCKSTREAM_H

/**
 *  @brief convert a stream of tokens into a stream of block objects
 * 
 *  designed to be used as a c++ standard container for transforming tokens into blocks
 *  read once, and loosely enforced read only (within the problem domain writing to a blockstream is not well defined)
 *  can not be copied !! if you need a second copy (for some reason, probably doing something wrong) then create a completely new instance
 *  however, the class can be moved using std::move
**/
class BlockStream {
    private:

    public:
        
};

#endif