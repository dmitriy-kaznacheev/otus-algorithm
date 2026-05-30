#pragma once
#include <string>
#include <vector>

namespace substr {

namespace detail {

template <typename Container>
std::vector<size_t> compute_prefix_function(const Container &needle) {
  const auto needle_len = static_cast<size_t>(needle.size());
  auto prefixes = std::vector<size_t>(needle_len, 0);

  size_t j = 0;
  for (size_t i = 1; i < needle_len; ++i) {
    while ((j > 0) && (needle[i] != needle[j])) {
      j = prefixes[j - 1];
    }
    if (needle[i] == needle[j]) {
      ++j;
    }
    prefixes[i] = j;
  }

  return prefixes;
}

} // namespace detail

template <typename Container>
std::vector<size_t> kmp_search(const Container &haystack,
                               const Container &needle) {
  const auto haystack_len = static_cast<size_t>(haystack.size());
  const auto needle_len = static_cast<size_t>(needle.size());

  if (needle_len == 0) {
    return {};
  }

  auto prefixes = detail::compute_prefix_function(needle);
  auto positions = std::vector<size_t>{};

  size_t j = 0;
  for (size_t i = 0; i < haystack_len; ++i) {
    while ((j > 0) && (haystack[i] != needle[j])) {
      j = prefixes[j - 1];
    }
    if (haystack[i] == needle[j]) {
      ++j;
    }
    if (j == needle_len) {
      positions.push_back(i - needle_len + 1);
      j = prefixes[j - 1];
    }
  }

  return positions;
}

} // namespace substr
