#include <gtest/gtest.h>
#include <vector>

#include <substr/kmp.h>

using namespace std::string_literals;

TEST(kmp, basic_search) {
  auto haystack{"ABCAAABCDEABC"s};
  auto needle{"ABC"s};

  auto expected = std::vector<size_t>{0, 5, 10};
  auto actual = substr::kmp_search(haystack, needle);
  EXPECT_EQ(expected, actual);
}

TEST(kmp, not_found) {
  auto haystack{"abcdefg"s};
  auto needle{"xyz"s};

  auto expected = std::vector<size_t>{};
  auto actual = substr::kmp_search(haystack, needle);
  EXPECT_EQ(expected, actual);
}

TEST(kmp, empty_needle) {
  auto haystack{"abcdefg"s};
  auto needle{""s};

  auto expected = std::vector<size_t>{};
  auto actual = substr::kmp_search(haystack, needle);
  EXPECT_EQ(expected, actual);
}

TEST(kmp, empty_haystack) {
  auto haystack{""s};
  auto needle{"xyz"s};

  auto expected = std::vector<size_t>{};
  auto actual = substr::kmp_search(haystack, needle);
  EXPECT_EQ(expected, actual);
}

TEST(kmp, needle_longer) {
  auto haystack{"short"s};
  auto needle{"needle_longer_than_haystack"s};

  auto expected = std::vector<size_t>{};
  auto actual = substr::kmp_search(haystack, needle);
  EXPECT_EQ(expected, actual);
}

TEST(kmp, full_text_exact_match) {
  auto haystack{"exact_match"s};
  auto needle{"exact_match"s};

  auto expected = std::vector<size_t>{0};
  auto actual = substr::kmp_search(haystack, needle);
  EXPECT_EQ(expected, actual);
}

TEST(kmp, overlapping_search) {
  auto haystack{"xxxxx"s};
  auto needle{"xxx"s};

  auto expected = std::vector<size_t>{0, 1, 2};
  auto actual = substr::kmp_search(haystack, needle);
  EXPECT_EQ(expected, actual);
}

TEST(kmp, single_symbol_needle) {
  auto haystack{"xxxxx"s};
  auto needle{"x"s};

  auto expected = std::vector<size_t>{0, 1, 2, 3, 4};
  auto actual = substr::kmp_search(haystack, needle);
  EXPECT_EQ(expected, actual);
}

TEST(kmp, vector_support) {
  auto haystack = std::vector{1, 2, 1, 2, 3, 1, 2, 1, 2, 4};
  auto needle = std::vector{1, 2, 1, 2, 4};

  auto expected = std::vector<size_t>{5};
  auto actual = substr::kmp_search(haystack, needle);
  EXPECT_EQ(expected, actual);
}
