#include <array>
#include <bitboard/utils.h>
#include <limits>

namespace bitboard {

namespace {
constexpr int MAX_VALUE = std::numeric_limits<uint16_t>::max() + 1;
consteval std::array<int, MAX_VALUE> precounting_set_bits() {
  std::array<int, MAX_VALUE> counts{};
  for (int val = 0; val != MAX_VALUE; ++val) {
    counts[val] = counts[val >> 1] + (val & 1);
  }
  return counts;
}

constexpr std::array<int, MAX_VALUE> COUNT_SET_BITS = precounting_set_bits();
} // namespace

int get_moves(uint64_t bitmask) {
  return COUNT_SET_BITS[(bitmask >> 48) & 0xFFFF] +
         COUNT_SET_BITS[(bitmask >> 32) & 0xFFFF] +
         COUNT_SET_BITS[(bitmask >> 16) & 0xFFFF] +
         COUNT_SET_BITS[(bitmask >> 0) & 0xFFFF];
}

} // namespace bitboard