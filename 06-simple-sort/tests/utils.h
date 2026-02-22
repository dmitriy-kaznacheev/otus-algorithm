#pragma once
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include <tuple>

using namespace std::string_literals;
using namespace std::string_view_literals;

const auto DATA_PATH{"../tests/data/"sv};
using FilePaths = std::pair<std::string, std::string>;

inline FilePaths get_file_paths(std::string test_dir, int index) {
  std::stringstream ss{};
  ss << DATA_PATH << std::move(test_dir) << "/"sv << "test."sv << index;
  return {ss.str() + ".in"s, ss.str() + ".out"s};
}

//--- timer -----------------------------------------------

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
