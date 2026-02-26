#pragma once
#include <algorithm>

namespace sort {
namespace selection {

template <typename It> void sort(It first, It last) {
  for (It it = first; it != last; ++it) {
    std::iter_swap(it, std::min_element(it, last));
  }
}

} // namespace selection
} // namespace sort
