#pragma once
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <optional>
#include <random>
#include <sstream>
#include <vector>

using namespace std::string_literals;
using namespace std::string_view_literals;

//--- timer -----------------------------------------------

class Timer {
public:
  Timer() : start_{std::chrono::high_resolution_clock::now()} {}
  size_t duration() {
    using namespace std::chrono;
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end_time - start_);
    return duration.count();
  }

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start_;
};

//--- test data file --------------------------------------

template <typename T> void generate_file(size_t count, std::string file_path) {
  static std::random_device rd{};
  static std::mt19937 gen{rd()};
  std::uniform_int_distribution<T> dist(std::numeric_limits<T>::min(),
                                        std::numeric_limits<T>::max());

  std::ofstream f{file_path, std::ios::binary};
  if (!f.is_open()) {
    std::cerr << "error: can't open file \""sv << file_path << "\""sv
              << std::endl;
    return;
  }

  f.write(reinterpret_cast<const char *>(&count), sizeof(count));
  for (; count != 0; --count) {
    T value = dist(gen);
    f.write(reinterpret_cast<const char *>(&value), sizeof(value));
  }
  f.close();
}

template <typename T> std::vector<T> read_file(std::string file_path) {
  std::ifstream f{file_path, std::ios::binary};
  if (!f.is_open()) {
    return {};
  }

  size_t size;
  f.read(reinterpret_cast<char *>(&size), sizeof(size));

  std::vector<T> v;
  {
    v.reserve(size);
    for (; size != 0; --size) {
      T value;
      f.read(reinterpret_cast<char *>(&value), sizeof(value));
      v.push_back(value);
    }
  }

  return v;
}
