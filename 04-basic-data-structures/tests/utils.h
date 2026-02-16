#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>

namespace basic_ds_test {

using namespace std::string_literals;
using namespace std::string_view_literals;

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

} // namespace basic_ds_test
