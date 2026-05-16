#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

#include <substr/boyer-moore.h>

using namespace std::string_literals;

TEST(boyer_moore, basic_search) {
  auto haystack{"ABCAAABCDEABC"s};
  auto needle{"ABC"s};

  auto expected = std::vector<size_t>{0, 5, 10};
  auto actual = substr::boyer_moore_search(haystack, needle);
  EXPECT_EQ(expected, actual);
}

TEST(boyer_moore, not_found) {
  auto haystack{"abcdefg"s};
  auto needle{"xyz"s};

  auto expected = std::vector<size_t>{};
  auto actual = substr::boyer_moore_search(haystack, needle);
  EXPECT_EQ(expected, actual);
}

TEST(boyer_moore, empty_needle) {
  auto haystack{"abcdefg"s};
  auto needle{""s};

  auto expected = std::vector<size_t>{};
  auto actual = substr::boyer_moore_search(haystack, needle);
  EXPECT_EQ(expected, actual);
}

TEST(boyer_moore, empty_haystack) {
  auto haystack{""s};
  auto needle{"xyz"s};

  auto expected = std::vector<size_t>{};
  auto actual = substr::boyer_moore_search(haystack, needle);
  EXPECT_EQ(expected, actual);
}

TEST(boyer_moore, needle_longer) {
  auto haystack{"short"s};
  auto needle{"needle_longer_than_haystack"s};

  auto expected = std::vector<size_t>{};
  auto actual = substr::boyer_moore_search(haystack, needle);
  EXPECT_EQ(expected, actual);
}

TEST(boyer_moore, full_text_exact_match) {
  auto haystack{"exact_match"s};
  auto needle{"exact_match"s};

  auto expected = std::vector<size_t>{0};
  auto actual = substr::boyer_moore_search(haystack, needle);
  EXPECT_EQ(expected, actual);
}

TEST(boyer_moore, overlapping_search) {
  auto haystack{"xxxxx"s};
  auto needle{"xxx"s};

  auto expected = std::vector<size_t>{0, 1, 2};
  auto actual = substr::boyer_moore_search(haystack, needle);
  EXPECT_EQ(expected, actual);
}

TEST(boyer_moore, single_symbol_needle) {
  auto haystack{"xxxxx"s};
  auto needle{"x"s};

  auto expected = std::vector<size_t>{0, 1, 2, 3, 4};
  auto actual = substr::boyer_moore_search(haystack, needle);
  EXPECT_EQ(expected, actual);
}

TEST(boyer_moore, wchar_support) {
  auto haystack = std::wstring{L"не жалею, не зову, не плачу"};
  auto needle = std::wstring{L"не"};

  auto expected = std::vector<size_t>{0, 10, 19};
  auto actual = substr::boyer_moore_search(haystack, needle);
  EXPECT_EQ(expected, actual);
}
