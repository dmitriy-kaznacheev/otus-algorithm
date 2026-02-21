#include "utils.h"

#include <functional>
#include <bitboard/king.h>
#include <bitboard/knight.h>
#include <bitboard/rook.h>
#include <bitboard/bishop.h>
#include <bitboard/queen.h>
#include <bitboard/utils.h>

using get_bitmask_fptr = std::function<uint64_t(int)>;

void test(get_bitmask_fptr get_bitmask, std::string test_name) {
  std::cout << "--- "sv << test_name << " ---"sv << std::endl;
  using namespace bitboard;

  for (int i = 0;; ++i) {
    auto [ipath, opath] = get_file_paths(test_name, i);
    auto in = get_file_content1<int>(std::move(ipath));
    auto out = get_file_content2<int, uint64_t>(std::move(opath));

    if (!in || !out) {
      break;
    }

    auto pos = in.value();
    auto [expected_moves, expected_mask] = out.value();

    {
      Timer t;
      auto actual_mask = get_bitmask(pos);
      auto actual_moves = get_moves(actual_mask);
      show_result(std::make_tuple(actual_moves, actual_mask),
                  std::make_tuple(expected_moves, expected_mask), i,
                  t.duration_ns());
    }
  }

  std::cout << std::endl;
}

int main() {
  using namespace bitboard;

  test(king::get_bitmask, "king"s);
  test(knight::get_bitmask, "knight"s);
  test(rook::get_bitmask, "rook"s);
  test(bishop::get_bitmask, "bishop"s);
  test(queen::get_bitmask, "queen"s);

  return 0;
}
