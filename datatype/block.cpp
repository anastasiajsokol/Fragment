#include "block.h"

void Block::append(std::variant<Token, Block> value){
    view.push_back(value);
}

Block::list_iterator_begin_type Block::begin(){
    return view.begin();
}

Block::list_iterator_end_type Block::end(){
    return view.end();
}