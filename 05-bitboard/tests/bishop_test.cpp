#include "bitboard_test.h"
#include "utils.h"

#include <bitboard/bishop.h>
#include <bitboard/utils.h>

void bishop_main() {
  std::cout << "--- bishop ---"sv << std::endl;
  using namespace bitboard;

  for (int i = 0;; ++i) {
    auto [ipath, opath] = get_file_paths("bishop"s, i);
    auto in = get_file_content1<uint64_t>(std::move(ipath));
    auto out = get_file_content2<int, uint64_t>(std::move(opath));

    if (!in || !out) {
      break;
    }

    auto pos = in.value();
    auto [expected_moves, expected_mask] = out.value();

    {
      Timer t;
      auto actual_mask = bishop::get_bitmask(pos);
      auto actual_moves = get_moves(actual_mask);
      show_result(std::make_tuple(actual_moves, actual_mask),
                  std::make_tuple(expected_moves, expected_mask), i,
                  t.duration_ns());
    }
  }

  std::cout << std::endl;
}
