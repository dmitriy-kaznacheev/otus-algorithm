#pragma once
#include <vector>

namespace sort {
namespace bubble {

template <typename It> void sort(It first, It last) {
  for (It i = first; i != last; ++i) {
    for (It j = first; j < i; ++j) {
      if (*i < *j) {
        std::iter_swap(i, j);
      }
    }
  }
}

} // namespace bubble
} // namespace sort
