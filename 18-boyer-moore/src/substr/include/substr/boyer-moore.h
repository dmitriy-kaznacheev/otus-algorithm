#pragma once
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

namespace substr {

namespace detail {

// сдвиги по плохому символу
template <typename T>
std::unordered_map<T, int>
build_bad_symbol_shifts(const std::basic_string<T> &needle) {
  std::unordered_map<T, int> shifts;
  const auto needle_len = static_cast<int>(needle.length());
  for (int i = 0; i < needle_len - 1; ++i) {
    shifts[needle[i]] = needle_len - 1 - i;
  }
  return shifts;
}

// для каждой позиции needle находит длину подстроки, совпадающей с его
// суффиксом
template <typename T>
std::vector<int> build_suffix_lengths(const std::basic_string<T> &needle) {
  const auto needle_len = static_cast<int>(needle.length());
  std::vector<int> suff(needle_len, 0);
  suff[needle_len - 1] = needle_len;

  auto window_left = needle_len - 1;
  auto window_right = 0;

  for (int i = needle_len - 2; i >= 0; --i) {
    if (i > window_left &&
        suff[i + needle_len - 1 - window_right] < i - window_left) {
      suff[i] = suff[i + needle_len - 1 - window_right];
    } else {
      if (i < window_left) {
        window_left = i;
      }
      window_right = i;
      while (window_left >= 0 &&
             needle[window_left] ==
                 needle[window_left + needle_len - 1 - window_right]) {
        --window_left;
      }
      suff[i] = window_right - window_left;
    }
  }
  return suff;
}

// сдвиги по хорошему суффиксу
template <typename T>
std::vector<int> build_good_suffix_shifts(const std::basic_string<T> &needle) {
  const auto needle_len = static_cast<int>(needle.length());
  std::vector<int> suffix_lengths = build_suffix_lengths(needle);
  std::vector<int> shifts(needle_len, needle_len);

  int j = 0;
  for (int i = needle_len - 1; i >= 0; --i) {
    if (suffix_lengths[i] == i + 1) {
      while (j < needle_len - 1 - i) {
        if (shifts[j] == needle_len) {
          shifts[j] = needle_len - 1 - i;
        }
        ++j;
      }
    }
  }

  for (int i = 0; i < needle_len - 1; ++i) {
    shifts[needle_len - 1 - suffix_lengths[i]] = needle_len - 1 - i;
  }

  return shifts;
}

} // namespace detail

template <typename T>
std::vector<size_t> boyer_moore_search(const std::basic_string<T> &haystack,
                                       const std::basic_string<T> &needle) {
  const auto haystack_len = static_cast<int>(haystack.length());
  const auto needle_len = static_cast<int>(needle.length());

  if ((needle_len == 0) || (needle_len > haystack_len)) {
    return {};
  }

  auto symbol_shifts = detail::build_bad_symbol_shifts(needle);
  auto suffix_shifts = detail::build_good_suffix_shifts(needle);
  std::vector<size_t> positions;

  auto shift = 0;
  while (shift <= (haystack_len - needle_len)) {
    auto i = needle_len - 1;

    // справа налево
    while ((i >= 0) && (needle[i] == haystack[shift + i])) {
      --i;
    }

    if (i < 0) {
      // совпадение
      positions.push_back(static_cast<size_t>(shift));
      shift += suffix_shifts[0];
    } else {
      // несовпадение
      auto mismatched_symbol = haystack[shift + i];

      // сдвиг по плохому символу
      auto it = symbol_shifts.find(mismatched_symbol);
      auto bad_symbol_distance =
          (it != symbol_shifts.end()) ? it->second : needle_len;
      auto symbol_shift = bad_symbol_distance - (needle_len - 1 - i);

      // сдвиг по хорошему суффиксу
      int suffix_shift = suffix_shifts[i];

      // шаг итогового сдвига
      shift += std::max(symbol_shift, suffix_shift);
    }
  }

  return positions;
}

} // namespace substr
