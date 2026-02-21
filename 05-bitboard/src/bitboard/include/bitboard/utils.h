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

template <typename MoveStrategy>
consteval std::array<Bitboard, BB_SIZE> precalc_masks(MoveStrategy pred) {
  std::array<Bitboard, BB_SIZE> masks{};

  for (uint8_t y1 = 0; y1 != BB_WIDTH; ++y1) {
    for (uint8_t x1 = 0; x1 != BB_WIDTH; ++x1) {

      uint8_t index = y1 * BB_WIDTH + x1;
      for (uint8_t y2 = 0; y2 != BB_WIDTH; ++y2) {
        for (uint8_t x2 = 0; x2 != BB_WIDTH; ++x2) {
          uint8_t dx = (x2 > x1) ? (x2 - x1) : (x1 - x2);
          uint8_t dy = (y2 > y1) ? (y2 - y1) : (y1 - y2);

          if (pred(dx, dy)) {
            uint8_t position = y2 * BB_WIDTH + x2;
            set_bit(masks[index], position);
          }
        }
      }
    }
  }
  return masks;
}

} // namespace bitboard