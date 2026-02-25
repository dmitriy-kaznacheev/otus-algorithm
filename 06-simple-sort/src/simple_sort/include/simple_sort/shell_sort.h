#pragma once
#include <simple_sort/insertion_sort.h>
#include <vector>

namespace sort {
namespace shell {

template <typename It> void sort(It first, It last) {
  auto size = std::distance(first, last);
  for (auto gap = size / 2; gap > 0; gap /= 2) {
    insertion::sort_with_gap<It>(first, last, gap);
  }
}

} // namespace shell
} // namespace sort
