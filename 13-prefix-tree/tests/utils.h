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
