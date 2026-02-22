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

} // namespace insertion
} // namespace sort
