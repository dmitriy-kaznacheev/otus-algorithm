#pragma once
#include <chrono>

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
