#pragma once
#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
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
    auto duration = duration_cast<seconds>(end_time - start_);
    return duration.count();
  }

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start_;
};

//--- result ----------------------------------------------

void show_result(bool result, size_t duration, size_t size,
                 std::string_view test_name) {
  std::cout << (result ? "[ + ] "sv : "[ - ] "sv) << std::setw(10) << test_name
            << ": "sv << size << " "sv << duration << "s"sv << std::endl;
}

//--- data preparatioh ------------------------------------

std::vector<std::string> generate_random_strings(size_t count, int min_len,
                                                 int max_len) {
  static std::mt19937 gen(42);

  std::uniform_int_distribution<int> len_dist{min_len, max_len};
  std::uniform_int_distribution<int> char_dist{'a', 'z'};

  std::vector<std::string> result;
  result.reserve(count);

  for (size_t i = 0; i != count; ++i) {
    std::string s(len_dist(gen), '\0');
    std::generate(s.begin(), s.end(),
                  [&char_dist]() { return static_cast<char>(char_dist(gen)); });
    result.push_back(std::move(s));
  }

  return result;
}
