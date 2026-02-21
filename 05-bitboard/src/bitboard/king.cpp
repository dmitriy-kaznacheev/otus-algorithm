#include <array>
#include <bitboard/king.h>
#include <bitboard/utils.h>

namespace bitboard {

namespace king {

namespace {
consteval bool king_move_strategy(uint8_t dx, uint8_t dy) {
  return (((dx == 1) && (dy == 0)) || 
          ((dx == 0) && (dy == 1)) ||
          ((dx == 1) && (dy == 1)));
}

constexpr std::array<Bitboard, BB_SIZE> masks = precalc_masks(king_move_strategy);
} // namespace

uint64_t get_bitmask(int pos) { return masks[pos]; }

} // namespace king

} // namespace bitboard