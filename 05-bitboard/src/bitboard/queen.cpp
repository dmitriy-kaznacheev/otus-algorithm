#include <array>
#include <bitboard/queen.h>
#include <bitboard/utils.h>

namespace bitboard {

namespace queen {

namespace {
consteval bool queen_move_strategy(uint8_t dx, uint8_t dy) {
  return (((dx == 0) && (dy != 0)) || 
          ((dx != 0) && (dy == 0)) ||
          ((dx == dy) && (dx != 0) && (dy != 0)));
}

constexpr std::array<Bitboard, BB_SIZE> masks = precalc_masks(queen_move_strategy);
} // namespace

uint64_t get_bitmask(int pos) { return masks[pos]; }

} // namespace queen

} // namespace bitboard