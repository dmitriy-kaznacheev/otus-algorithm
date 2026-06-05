#include "utils.h"
#include <dp/christmas_tree.h>
#include <gtest/gtest.h>

using Tree = std::vector<std::vector<int>>;

TEST(manual_christmas_tree_test, Example1) {
  auto tree = Tree{{7}, {3, 8}, {8, 1, 0}};
  EXPECT_EQ(dp::max_garland_sum(tree), 18);
}

TEST(manual_christmas_tree_test, large) {
  auto tree = Tree{{3}, {7, 4}, {2, 4, 6}, {8, 5, 9, 3}};
  EXPECT_EQ(dp::max_garland_sum(tree), 23);
}

TEST(manual_christmas_tree_test, single) {
  auto tree = Tree{{5}};
  EXPECT_EQ(dp::max_garland_sum(tree), 5);
}

TEST(manual_christmas_tree_test, symmetric) {
  auto tree = Tree{{1}, {1, 1}, {1, 1, 1}};
  EXPECT_EQ(dp::max_garland_sum(tree), 3);
}

TEST(manual_christmas_tree_test, empty) {
  auto tree = Tree{};
  EXPECT_EQ(dp::max_garland_sum(tree), 0);
}

namespace {
Tree parse(const std::string &input) {
  std::istringstream ss(input);
  std::string line;

  int n;
  {
    ss >> n;
    std::getline(ss, line); // пропустить остаток первой строки
  }

  Tree result;
  for (int i = 0; i < n; ++i) {
    std::getline(ss, line);
    std::istringstream ss_line(line);

    {
      std::vector<int> row;
      int num;
      while (ss_line >> num) {
        row.push_back(num);
      }

      result.push_back(row);
    }
  }

  return result;
}
} // namespace

class ChristmasTreeTest
    : public ::testing::TestWithParam<std::pair<std::string, std::string>> {};

TEST_P(ChristmasTreeTest, file) {
  auto [input_file, output_file] = GetParam();
  std::string input = read_file(input_file);
  std::string output = read_file(output_file);

  auto tree = parse(input);
  int expected = std::stoi(output);
  EXPECT_EQ(dp::max_garland_sum(tree), expected);
}

INSTANTIATE_TEST_SUITE_P(
    DataFiles, ChristmasTreeTest,
    ::testing::ValuesIn(find_test_files(DATA_DIR "/christmas_tree")));