#include <array>
#include <bitboard/king.h>
#include <bitboard/utils.h>

namespace bitboard {

namespace king {

namespace {
consteval std::array<Bitboard, BB_SIZE> precalc_masks() {
  std::array<Bitboard, BB_SIZE> masks{};

  for (uint8_t y1 = 0; y1 != BB_WIDTH; ++y1) {
    for (uint8_t x1 = 0; x1 != BB_WIDTH; ++x1) {

      uint8_t index = y1 * BB_WIDTH + x1;
      for (uint8_t y2 = 0; y2 != BB_WIDTH; ++y2) {
        for (uint8_t x2 = 0; x2 != BB_WIDTH; ++x2) {
          uint8_t dx = abs_substract(x1, x2);
          uint8_t dy = abs_substract(y1, y2);

          if (((dx == 1) && (dy == 0)) || ((dx == 0) && (dy == 1)) ||
              ((dx == 1) && (dy == 1))) {
            uint8_t position = y2 * BB_WIDTH + x2;
            set_bit(masks[index], position);
          }
        }
      }
    }
  }
  return masks;
}

constexpr std::array<Bitboard, BB_SIZE> masks = precalc_masks();
} // namespace

uint64_t get_bitmask(int pos) { return masks[pos]; }

} // namespace king

} // namespace bitboard