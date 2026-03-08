#pragma once
#include <linear_sort/counting_sort.h>

#include <algorithm>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

namespace sort {
namespace radix {

template <typename It> void sort(It first, It last) {
  if (first == last) {
    return;
  }

  const auto max = *std::max_element(first, last);
  for (int exp = 1; (max / exp) > 0; exp *= 10) {
    counting::sort_radix(first, last, exp);
  }
}

} // namespace radix
} // namespace sort