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

template <typename T>
inline std::optional<T> get_file_content1(std::string file_path) {
  std::fstream f{file_path};
  T value;
  if (f >> value) {
    return value;
  } else {
    return std::nullopt;
  }
}

template <typename T1, typename T2 = T1>
inline std::optional<std::tuple<T1, T2>>
get_file_content2(std::string file_path) {
  std::fstream f{file_path};
  T1 value1;
  T2 value2;
  if (f >> value1 >> value2) {
    return std::make_tuple(value1, value2);
  } else {
    return std::nullopt;
  }
}

template <typename T1, typename T2>
inline void show_result(std::tuple<T1, T2> actual, std::tuple<T1, T2> expected,
                        int test_index, size_t duration_ms) {

  bool is_equal = false;
  if constexpr (std::is_floating_point_v<T1> || std::is_floating_point_v<T2>) {
    static_assert(false, "comparison for floating point is not implemented");
  } else {
    is_equal = (actual == expected);
  }

  if (is_equal) {
    std::cout << "[ + ] test_"sv << test_index << ": "sv << duration_ms
              << " ns"sv << std::endl;
  } else {
    std::cout << "[ - ] test_"sv << test_index << ": "sv << "{n:"sv
              << std::get<0>(expected) << ", m:"sv << std::get<1>(expected)
              << "}"sv << " != "sv << "{n:"sv << std::get<0>(actual) << ", m:"sv
              << std::get<1>(actual) << "}"sv << std::endl;
  }
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
