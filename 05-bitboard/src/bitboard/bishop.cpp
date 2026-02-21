#include <array>
#include <bitboard/bishop.h>
#include <bitboard/utils.h>

namespace bitboard {

namespace bishop {

namespace {
consteval bool bishop_move_strategy(uint8_t dx, uint8_t dy) {
  return ((dx == dy) && (dx != 0) && (dy != 0));
}

constexpr std::array<Bitboard, BB_SIZE> masks = precalc_masks(bishop_move_strategy);
} // namespace

uint64_t get_bitmask(int pos) { return masks[pos]; }

} // namespace bishop

} // namespace bitboard