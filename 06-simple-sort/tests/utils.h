#pragma once
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <optional>
#include <sstream>
#include <vector>

using namespace std::string_literals;
using namespace std::string_view_literals;

const auto DATA_PATH{"../tests/data/"sv};
using FilePaths = std::pair<std::string, std::string>;

inline FilePaths get_file_paths(std::string test_dir, int index) {
  std::stringstream ss{};
  ss << DATA_PATH << std::move(test_dir) << "/"sv << "test."sv << index;
  return {ss.str() + ".in"s, ss.str() + ".out"s};
}

template <typename T>
inline std::vector<T> read_vector(std::string file_path, size_t size = 0) {
  std::fstream f{file_path};
  if (!f.is_open()) {
    return {};
  }

  if (size == 0) {
    f >> size;
  }

  std::vector<T> v{std::istream_iterator<T>(f), std::istream_iterator<T>()};

  if (size != v.size()) {
    v.clear();
  }

  return v;
}

template <typename T>
inline void show_result(std::vector<T> actual, std::vector<T> expected,
                        int test_index, size_t duration) {
  bool is_equal{actual == expected};
  std::cout << (is_equal ? "[ + ]"sv : "[ - ]"sv) << " test_"sv << test_index
            << ": "sv << std::setw(8) << expected.size() << " "sv << duration
            << " us"sv << std::endl;
}

//--- timer -----------------------------------------------

class Timer {
public:
  Timer() : start_{std::chrono::high_resolution_clock::now()} {}
  size_t duration_ns() {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        end_time - start_);
    return duration.count();
  }

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start_;
};
