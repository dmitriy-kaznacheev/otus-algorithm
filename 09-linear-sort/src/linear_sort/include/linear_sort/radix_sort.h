#pragma once
#include <algorithm>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

namespace sort {
namespace radix {

namespace detail {

template <typename T> class Radix final {
  using Data = std::vector<T>;
  using Iterator = Data::iterator;

public:
  template <typename It> Radix(It first, It last) {
    if (first == last) {
      return;
    }

    const auto max = *std::max_element(first, last);
    const auto size = std::distance(first, last);

    data_.resize(size);
    std::copy(first, last, data_.begin());

    for (int exp = 1; (max / exp) > 0; exp *= 10) {
      counting_sort_radix(first, last, exp);
    }
  }

  Iterator begin() { return data_.begin(); }
  Iterator end() { return data_.end(); }

private:
  template <typename It> void counting_sort_radix(It first, It last, int exp) {
    const auto range = 10;
    std::vector<size_t> count(range, 0);

    for (auto it = first; it != last; ++it) {
      int icount = ((*it) / exp) % range;
      ++count[icount];
    }

    std::inclusive_scan(count.begin(), count.end(), count.begin());

    std::reverse_iterator<It> rfirst{last};
    std::reverse_iterator<It> rlast{first};
    for (auto it = rfirst; it != rlast; ++it) {
      auto icount = ((*it) / exp) % range;
      auto idata = count[icount] - 1;
      data_[idata] = *it;
      --count[icount];
    }

    std::move(data_.begin(), data_.end(), first);
  }

private:
  Data data_;
};

template <typename It>
Radix(It, It) -> Radix<typename std::iterator_traits<It>::value_type>;

} // namespace detail

template <typename It> void sort(It first, It last) {
  using namespace detail;
  Radix radix{first, last};
  std::move(radix.begin(), radix.end(), first);
}

} // namespace radix
} // namespace sort