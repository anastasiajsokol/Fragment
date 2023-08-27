#include "block.h"

Block::Block(const Token::TokenPosition position) noexcept : position(position) {}
Block::Block() noexcept {}

Block& Block::append(std::variant<Token, Block> value) {
    view.push_back(value);
    return *this;
}

Block::list_iterator_begin_type Block::begin() noexcept {
    return view.begin();
}

Block::list_iterator_end_type Block::end() noexcept {
    return view.end();
}

size_t Block::size() const noexcept {
    return view.size();
}