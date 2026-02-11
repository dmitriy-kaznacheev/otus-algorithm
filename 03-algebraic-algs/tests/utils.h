#pragma once

#include <array>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>

using namespace std::string_literals;
using namespace std::string_view_literals;

const auto DATA_PATH{"../tests/data/"sv};
using FilePaths = std::pair<std::string, std::string>;

FilePaths get_file_paths(std::string test_dir, int index) {
  std::stringstream ss{};
  ss << DATA_PATH << std::move(test_dir) << "/"sv << "test."sv << index;
  return {ss.str() + ".in"s, ss.str() + ".out"s};
}

template <typename T, size_t size>
std::optional<std::array<T, size>> get_file_content(std::string file_path) {
  std::fstream f{file_path};
  std::array<T, size> result;
  for (int i = 0, end = result.size(); i != end; ++i) {
    if (!(f >> result[i])) {
      return std::nullopt;
    }
  }
  return result;
}

template <typename T>
void show_result(T actual, T expected, int test_index, size_t duration_ms,
                 std::string_view test_name) {
  if (actual == expected) {
    std::cout << "[ + ] "sv << test_name << "_"sv << test_index << ": "sv
              << duration_ms << " ns"sv << std::endl;
  } else {
    std::cout << "[ - ] "sv << test_name << "_"sv << test_index << ": "sv
              << expected << " != "sv << actual << std::endl;
  }
}

class Timer {
public:
  Timer() : start_{std::chrono::high_resolution_clock::now()} {}
  size_t duration_ns() {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_);
    return duration.count();
  }

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start_;
};
