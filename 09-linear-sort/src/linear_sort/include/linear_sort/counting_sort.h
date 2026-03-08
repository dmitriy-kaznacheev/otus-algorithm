#pragma once
#include <algorithm>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

namespace sort {
namespace counting {

namespace detail {

template <typename T> class Counter final {
  using Data = std::vector<T>;
  using Iterator = Data::iterator;

public:
  template <typename It> Counter(It first, It last) {
    if (first == last) {
      return;
    }

    const auto size = std::distance(first, last);
    const auto [min_it, max_it] = std::minmax_element(first, last);
    const auto range = (*max_it) - (*min_it) + 1;

    std::vector<size_t> count(range, 0);
    for (auto it = first; it != last; ++it) {
      auto icount = (*it) - (*min_it);
      ++count[icount];
    }
    std::inclusive_scan(count.begin(), count.end(), count.begin());

    data_.resize(size);
    std::reverse_iterator<It> rfirst{last};
    std::reverse_iterator<It> rlast{first};
    for (auto it = rfirst; it != rlast; ++it) {
      auto icount = (*it) - (*min_it);
      auto idata = count[icount] - 1;
      data_[idata] = *it;
      --count[icount];
    }
  }

  Iterator begin() { return data_.begin(); }
  Iterator end() { return data_.end(); }

private:
  Data data_;
};

template <typename It>
Counter(It, It) -> Counter<typename std::iterator_traits<It>::value_type>;

} // namespace detail

template <typename It> void sort(It first, It last) {
  using namespace detail;
  Counter counter{first, last};
  std::move(counter.begin(), counter.end(), first);
}

} // namespace counting
} // namespace sort