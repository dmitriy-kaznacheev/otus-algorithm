#include "solver/solver.h"
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>

using namespace std::string_literals;

const auto DATA_PATH{"../tests/data/"s};
using FilePaths = std::pair<std::string, std::string>;

FilePaths get_file_paths(int index) {
  std::stringstream ss{};
  ss << DATA_PATH << "test."s << index;
  return {ss.str() + ".in"s, ss.str() + ".out"s};
}

std::optional<long> get_file_content(std::string file_path) {
  std::fstream f{file_path};
  if (!f) {
    return std::nullopt;
  }

  long result;
  f >> result;
  return result;
}

template <typename T> void show_result(T actual, T expected, int test_index) {
  if (actual == expected) {
    std::cout << "[ + ] test #" << test_index << ": " << actual << std::endl;
  } else {
    std::cout << "[ - ] test #" << test_index << '\n'
              << "  actual:   " << actual << '\n'
              << "  expected: " << expected << std::endl;
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
