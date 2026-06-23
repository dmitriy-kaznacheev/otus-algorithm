#include <gtest/gtest.h>

#include <bloom_filter/bloom_filter.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std::string_literals;

namespace {

std::pair<std::vector<std::string>, std::vector<std::string>>
gen_dataset(size_t train_size, size_t test_size) {

  std::vector<std::string> train;
  train.reserve(train_size);
  for (size_t i = 0; i < train_size; ++i) {
    train.push_back("element_"s + std::to_string(i));
  }

  std::random_device rd;
  std::mt19937 g{rd()};
  std::shuffle(train.begin(), train.end(), g);

  std::vector<std::string> test;
  test.reserve(test_size);
  std::unordered_set<std::string> train_set(train.begin(), train.end());

  auto offset = train_size;
  while (test.size() < test_size) {
    std::string candidate = "element_"s + std::to_string(offset++);
    if (train_set.count(candidate) == 0) {
      test.push_back(candidate);
    }
  }
  return {train, test};
}

} // namespace

TEST(BloomFilterTest, basic) {
  auto f = bf::BloomFilter{1000, 0.01};

  f.insert("aaa"s);
  f.insert("bbb"s);
  f.insert("ccc"s);

  EXPECT_TRUE(f.contains("aaa"s));
  EXPECT_TRUE(f.contains("bbb"s));
  EXPECT_TRUE(f.contains("ccc"s));
  EXPECT_FALSE(f.contains("ddd"s));
  EXPECT_FALSE(f.contains("eee"s));
}

TEST(BloomFilterTest, empty_filter) {
  auto f = bf::BloomFilter{1000, 0.01};
  EXPECT_FALSE(f.contains("anything"s));
}

TEST(BloomFilterTest, small_filter) {
  const int size = 10;
  auto f = bf::BloomFilter{size, 0.1};

  for (int i = 0; i != size; ++i) {
    f.insert("item"s + std::to_string(i));
  }

  for (int i = 0; i != size; ++i) {
    EXPECT_TRUE(f.contains("item"s + std::to_string(i)));
  }
}

TEST(BloomFilterTest, false_positive_rate) {
  const size_t capacity = 100000;
  const double error_rate = 0.05;

  auto [train, test] = gen_dataset(capacity, 10000);

  auto f = bf::BloomFilter{capacity, error_rate};

  std::cout << "\n===== parameters ================" << std::endl;
  std::cout << "capacity:     " << capacity << std::endl;
  std::cout << "target error: " << error_rate * 100 << "%" << std::endl;
  std::cout << "bit array:    " << f.bit_size() << " bits" << std::endl;
  std::cout << "hash funcs:   " << f.hash_count() << std::endl;
  std::cout << "memory:       " << std::fixed << std::setprecision(2)
            << f.bit_size() / 8.0 / 1024 << " KB" << std::endl;

  for (const auto &item : train) {
    f.insert(item);
  }

  size_t false_negatives =
      std::count_if(train.begin(), train.end(),
                    [&f](const auto &item) { return !f.contains(item); });
  std::cout << "----- results -----" << std::endl;
  std::cout << "false negatives: " << false_negatives << " (must be 0)"
            << std::endl;
  EXPECT_EQ(false_negatives, 0);

  size_t false_positives =
      std::count_if(test.begin(), test.end(),
                    [&f](const auto &item) { return f.contains(item); });

  double observed = static_cast<double>(false_positives) / test.size();
  double expected_fp = test.size() * error_rate;
  double std_dev = std::sqrt(test.size() * error_rate * (1.0 - error_rate));
  double z_score = (false_positives - expected_fp) / std_dev;

  std::cout << "false positives: " << false_positives << std::endl;

  std::cout << std::fixed << std::setprecision(2);
  std::cout << "expected rate:   " << error_rate * 100 << "%" << std::endl;
  std::cout << "observed rate:   " << observed * 100 << "%" << std::endl;
  std::cout << "z-score:         " << z_score << " ";
  std::cout << (std::abs(z_score) <= 2.0 ? "(ok)" : "(err)") << std::endl;
  std::cout << "=================================\n" << std::endl;

  EXPECT_LE(observed, error_rate * 1.2);
  EXPECT_GE(observed, error_rate * 0.1);
}
