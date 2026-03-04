#pragma once
#include <algorithm>
#include <iterator>
#include <vector>

namespace sort {
namespace merge {

namespace {
template <typename It> void merge_ranges(It first, It middle, It last) {
  using value_type = typename std::iterator_traits<It>::value_type;
  auto size = std::distance(first, last);

  std::vector<value_type> temp(size);
  std::merge(first, middle, middle, last, std::begin(temp));
  std::move(std::begin(temp), std::end(temp), first);
}
} // namespace

template <typename It> void sort(It first, It last) {
  auto size = std::distance(first, last);
  if (size <= 1) {
    return;
  }

  It middle = std::next(first, size / 2);
  merge::sort(first, middle);
  merge::sort(middle, last);
  merge_ranges(first, middle, last);
}

} // namespace merge
} // namespace sort
