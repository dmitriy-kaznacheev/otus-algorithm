#include <array>
#include <bitboard/knight.h>
#include <bitboard/utils.h>

namespace bitboard {

namespace knight {

namespace {
consteval bool knight_move_strategy(uint8_t dx, uint8_t dy) {
  return (((dx == 2) && (dy == 1)) || 
          ((dx == 1) && (dy == 2)));
}

constexpr std::array<Bitboard, BB_SIZE> masks = precalc_masks(knight_move_strategy);
} // namespace

uint64_t get_bitmask(int pos) { return masks[pos]; }

} // namespace knight

} // namespace bitboard