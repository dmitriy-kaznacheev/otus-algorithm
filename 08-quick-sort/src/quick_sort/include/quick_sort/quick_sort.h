#pragma once
#include <algorithm>
#include <iterator>

namespace sort {
namespace quick {

namespace {
template <typename It> struct Bound {
  It lhs, rhs;
};

template <typename It> Bound<It> partition(It first, It last) {
  auto pivot = *first; // TODO выбрать случайный элемент
  // clang-format off
  return {
    std::partition(first, last, [pivot](const auto &elem) { return (elem <  pivot); }),
    std::partition(first, last, [pivot](const auto &elem) { return (elem <= pivot); })
  };
  // clang-format on
}
} // namespace

template <typename It> void sort(It first, It last) {
  if (first != last) {
    auto bound = partition(first, last);
    quick::sort(first, bound.lhs);
    quick::sort(bound.rhs, last);
  }
}

} // namespace quick
} // namespace sort
