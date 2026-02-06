#include "solver/solver.h"
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>

using namespace std::string_literals;
using namespace std::string_view_literals;

const auto DATA_PATH{"../tests/data/"s};
using FilePaths = std::pair<std::string, std::string>;

FilePaths get_file_paths(int index) {
  std::stringstream ss{};
  ss << DATA_PATH << "test."s << index;
  return {ss.str() + ".in"s, ss.str() + ".out"s};
}

std::optional<long> get_file_content(std::string file_path) {
  std::fstream f{file_path};
  long value;
  if (f >> value) {
    return value;
  } else {
    return std::nullopt;
  }
}

template <typename T> void show_result(T actual, T expected, int test_index) {
  if (actual == expected) {
    std::cout << "[ + ] test #"sv << test_index << ": "sv << actual << std::endl;
  } else {
    std::cout << "[ - ] test #"sv << test_index << '\n'
              << "  actual:   "sv << actual << '\n'
              << "  expected: "sv << expected << std::endl;
  }
}

int main() {
  for (int i = 0;; ++i) {
    auto paths = get_file_paths(i);
    auto in = get_file_content(std::move(paths.first));
    auto out = get_file_content(std::move(paths.second));

    if (!in || !out) {
      break;
    }

    {
      solver::HappyTickets ht{in.value()};
      auto actual = ht.run();
      auto expected = out.value();
      show_result(actual, expected, i);
    }
  }

  return 0;
}
