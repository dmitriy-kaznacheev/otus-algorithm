#include "bitboard_test.h"
#include "utils.h"

#include <bitboard/rook.h>
#include <bitboard/utils.h>

void rook_main() {
  std::cout << "--- rook -----"sv << std::endl;
  using namespace bitboard;

  for (int i = 0;; ++i) {
    auto [ipath, opath] = get_file_paths("rook"s, i);
    auto in = get_file_content1<uint64_t>(std::move(ipath));
    auto out = get_file_content2<int, uint64_t>(std::move(opath));

    if (!in || !out) {
      break;
    }

    auto pos = in.value();
    auto [expected_moves, expected_mask] = out.value();

    {
      Timer t;
      auto actual_mask = rook::get_bitmask(pos);
      auto actual_moves = get_moves(actual_mask);
      show_result(std::make_tuple(actual_moves, actual_mask),
                  std::make_tuple(expected_moves, expected_mask), i,
                  t.duration_ns());
    }
  }

  std::cout << std::endl;
}
