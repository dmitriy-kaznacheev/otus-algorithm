#pragma once
#include <algorithm>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

namespace sort {
namespace counting {

namespace detail {

template <typename Indexer, typename It,
          typename T = std::iterator_traits<It>::value_type>
std::vector<size_t> get_count(It first, It last, Indexer indexer, T range) {
  std::vector<size_t> count(range, 0);
  for (auto it = first; it != last; ++it) {
    auto icount = indexer(*it);
    ++count[icount];
  }

  std::inclusive_scan(count.begin(), count.end(), count.begin());
  return count;
}

template <typename Indexer, typename It>
void update_data(It first, It last, Indexer indexer,
                 std::vector<size_t> &count) {
  using value_type = std::iterator_traits<It>::value_type;
  const auto size = std::distance(first, last);

  std::vector<value_type> data(size, 0);

  std::reverse_iterator<It> rfirst{last};
  std::reverse_iterator<It> rlast{first};
  for (auto it = rfirst; it != rlast; ++it) {
    auto icount = indexer(*it);
    auto idata = count[icount] - 1;
    data[idata] = *it;
    --count[icount];
  }

  std::move(data.begin(), data.end(), first);
}

} // namespace detail

template <typename It> void sort(It first, It last) {
  if (first == last) {
    return;
  }

  using namespace detail;
  const auto [min_it, max_it] = std::minmax_element(first, last);
  const auto range = (*max_it) - (*min_it) + 1;

  auto indexer = [&min_it](const auto &value) { return value - (*min_it); };

  auto count = get_count(first, last, indexer, range);
  update_data(first, last, indexer, count);
}

template <typename It> void sort_radix(It first, It last, int exp) {
  if (first == last) {
    return;
  }

  using namespace detail;
  const auto range = 10;

  auto indexer = [exp, range](const auto &value) {
    return (value / exp) % range;
  };

  auto count = get_count(first, last, indexer, range);
  update_data(first, last, indexer, count);
}

} // namespace counting
} // namespace sort