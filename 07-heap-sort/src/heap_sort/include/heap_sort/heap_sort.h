#pragma once
#include <iterator>

namespace sort {
namespace heap {

namespace {
template <typename It> void sift_down(It first, It last, It current) {
  auto size = std::distance(first, last);
  auto cur_index = std::distance(first, current);
  auto lch_index = 2 * cur_index + 1;
  auto rch_index = 2 * cur_index + 2;

  auto largest_index = cur_index;
  if ((lch_index < size) && (*(first + lch_index) > *(first + largest_index))) {
    largest_index = lch_index;
  }
  if ((rch_index < size) && (*(first + rch_index) > *(first + largest_index))) {
    largest_index = rch_index;
  }
  if (largest_index != cur_index) {
    std::swap(*(first + cur_index), *(first + largest_index));
    sift_down(first, last, first + largest_index);
  }
}
} // namespace

template <typename It> void sort(It first, It last) {
  auto size = std::distance(first, last);
  auto half_size = size / 2;

  for (int i = half_size - 1; i >= 0; --i) {
    sift_down(first, last, first + i);
  }

  for (int i = size - 1; i > 0; --i) {
    std::swap(*first, *(first + i));
    sift_down(first, first + i, first);
  }
}

} // namespace heap
} // namespace sort
