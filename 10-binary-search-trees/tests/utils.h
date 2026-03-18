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

static std::random_device rd;
static std::mt19937 gen{rd()};

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

//--- data preparatioh ------------------------------------

template <typename It, typename T = std::iterator_traits<It>::value_type>
std::vector<T> choose_random_items(It first, It last, size_t size) {
  std::vector<T> v(first, last);
  std::shuffle(v.begin(), v.end(), gen);
  v.resize(size);
  return v;
}

template <typename T>
std::vector<T> gen_random(size_t size, T min = std::numeric_limits<T>::min(),
                          T max = std::numeric_limits<T>::max()) {
  static std::uniform_int_distribution<T> dist(min, max);
  auto gen_ = [&]() { return dist(gen); };

  std::vector<T> v(size);
  std::generate(v.begin(), v.end(), gen_);
  return v;
}

template <typename T> std::vector<T> gen_increasing(size_t size) {
  std::vector<T> v(size);
  std::iota(v.begin(), v.end(), 1);
  return v;
}

//--- result ----------------------------------------------

template <typename Tree, typename It>
bool check(const Tree &tree, It first, It last) {
  using value_type = typename std::iterator_traits<It>::value_type;
  auto size = std::distance(first, last);
  std::vector<value_type> flat;
  {
    flat.reserve(size);
    tree.traverse([&flat](auto value) { flat.push_back(value); });
  }
  return std::equal(first, last, flat.begin(), flat.end());
}

void show_result(bool result, size_t duration, size_t size,
                 std::string_view test_name) {
  std::cout << (result ? "[ + ] "sv : "[ - ] "sv) << test_name << ": "sv
            << std::setw(8) << size << " "sv << duration << "s"sv << std::endl;
}
