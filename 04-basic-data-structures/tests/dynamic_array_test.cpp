#include "basic_ds_test.h"
#include "dynamic_array/dynamic_array.h"
#include "utils.h"

namespace basic_ds_test {

using namespace basic_ds;

void plus_1_test(size_t n) {
  Timer t;
  DynamicArray<int, LinearBuffer<int, 1>> arr;
  for (int i = 0; i != n; ++i) {
    arr.add(i);
  }
  std::cout << std::setw(8) << t.duration_ns() << " us"sv;
}

void plus_100_test(size_t n) {
  Timer t;
  DynamicArray<int, LinearBuffer<int, 100>> arr;
  for (int i = 0; i != n; ++i) {
    arr.add(i);
  }
  std::cout << std::setw(8) << t.duration_ns() << " us"sv;
}

void mult_2_test(size_t n) {
  Timer t;
  DynamicArray<int, LinearBuffer<int, 1, 2>> arr;
  for (int i = 0; i != n; ++i) {
    arr.add(i);
  }
  std::cout << std::setw(8) << t.duration_ns() << " us"sv;
}

void dynamic_array_test() {
  std::cout << "--- dynamic array tests ---"sv << std::endl;

  std::cout << "     n \t     +1 \t  +100 \t   x2"sv << std::endl;
  for (size_t n = 100; n != 1'000'000; n *= 10) {
    std::cout << std::setw(6) << n << ":"sv;
    plus_1_test(n);
    plus_100_test(n);
    mult_2_test(n);
    std::cout << std::endl;
  }

  std::cout << std::endl;
}

} // namespace basic_ds_test
