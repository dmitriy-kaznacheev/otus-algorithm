#pragma once
#include <cstdint>

namespace bitboard {

constexpr uint8_t BB_WIDTH = 8;
constexpr uint8_t BB_SIZE = BB_WIDTH * BB_WIDTH;

using Bitboard = uint64_t;
int get_moves(uint64_t bitmask);

consteval void set_bit(Bitboard &bb, uint8_t bit) { bb |= (1ull << bit); }

consteval void clr_bit(Bitboard &bb, uint8_t bit) { bb &= ~(1ull << bit); }

consteval bool get_bit(Bitboard bb, uint8_t bit) {
  return (bb & (1ull << bit));
}

constexpr uint8_t abs_substract(uint8_t lhs, uint8_t rhs) {
    return (lhs > rhs) ? (lhs - rhs) : (rhs - lhs);
}

} // namespace bitboard