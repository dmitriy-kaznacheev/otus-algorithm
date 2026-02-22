#pragma once
#include <algorithm>
#include <vector>

namespace sort {
namespace insertion {

template <typename It> void sort(It first, It last) {
  std::iter_swap(first, std::min_element(first, last));
  for (It b = first; ++b < last; first = b) {
    for (It c = b; *c < *first; --c, --first) {
      std::iter_swap(first, c);
    }
  }
}

template <typename It>
void sort_with_gap(It first, It last,
                   typename std::iterator_traits<It>::difference_type gap) {
  for (auto i = first + gap; i < last; ++i) {
    auto key = *i;
    auto j = i;
    // Перемещаем элементы, пока не найдем правильную позицию
    while (j - gap >= first && *(j - gap) > key) {
      *j = *(j - gap);
      j -= gap;
    }
    *j = key;
  }
}

} // namespace insertion
} // namespace sort
