#pragma once
#include <algorithm>
#include <iterator>
#include <random>

namespace sort {
namespace quick {

namespace detail {
template <typename It> struct Bound {
  It lhs, rhs;
};

template <typename It> It get_random_iterator(It first, It last) {
  auto size = std::distance(first, last);
  if (size == 0) {
    return last;
  }
  static std::random_device rd{};
  static std::mt19937 gen{rd()};
  std::uniform_int_distribution<decltype(size)> dist(0, size - 1);
  return std::next(first, dist(gen));
}

template <typename It> Bound<It> partition(It first, It last) {
  auto pivot = *get_random_iterator(first, last);
  // clang-format off
  return {
    std::partition(first, last, [pivot](const auto &elem) { return (elem <  pivot); }),
    std::partition(first, last, [pivot](const auto &elem) { return (elem <= pivot); })
  };
  // clang-format on
}
} // namespace detail

template <typename It> void sort(It first, It last) {
  using namespace detail;
  if (first != last) {
    auto bound = partition(first, last);
    quick::sort(first, bound.lhs);
    quick::sort(bound.rhs, last);
  }
}

} // namespace quick
} // namespace sort
