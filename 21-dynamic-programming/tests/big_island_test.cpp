#include "utils.h"
#include <dp/big_island.h>
#include <gtest/gtest.h>

using Grid = std::vector<std::vector<int>>;

TEST(manual_big_island_test, two_islands) {
  auto grid = Grid{{1, 1, 0}, {0, 1, 0}, {0, 0, 1}};
  EXPECT_EQ(dp::count_islands(grid), 2);
}

TEST(manual_big_island_test, five_islands) {
  auto grid = Grid{{1, 1, 0, 1}, {1, 0, 0, 0}, {0, 0, 1, 0}, {1, 0, 0, 1}};
  EXPECT_EQ(dp::count_islands(grid), 5);
}

TEST(manual_big_island_test, not_connected) {
  auto grid = Grid{{1, 0}, {0, 1}};
  EXPECT_EQ(dp::count_islands(grid), 2);
}

TEST(manual_big_island_test, single_islands) {
  auto grid = Grid{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
  EXPECT_EQ(dp::count_islands(grid), 1);
}

TEST(manual_big_island_test, to_islands) {
  auto grid = Grid{{0, 0}, {0, 0}};
  EXPECT_EQ(dp::count_islands(grid), 0);
}

TEST(manual_big_island_test, single_cell) {
  auto grid = Grid{{1}};
  EXPECT_EQ(dp::count_islands(grid), 1);
}

TEST(manual_big_island_test, l_shaped_islands) {
  auto grid = Grid{{1, 0}, {1, 1}};
  EXPECT_EQ(dp::count_islands(grid), 1);
}

TEST(manual_big_island_test, empty_grid) {
  auto grid = Grid{};
  EXPECT_EQ(dp::count_islands(grid), 0);
}

namespace {
Grid parse(const std::string &input) {
  std::istringstream ss(input);
  std::string line;

  int n;
  {
    ss >> n;
    std::getline(ss, line); // пропустить остаток первой строки
  }

  Grid result;
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

class BigIslandTest
    : public ::testing::TestWithParam<std::pair<std::string, std::string>> {};

TEST_P(BigIslandTest, file) {
  auto [input_file, output_file] = GetParam();
  std::string input = read_file(input_file);
  std::string output = read_file(output_file);

  auto grid = parse(input);
  int expected = std::stoi(output);
  EXPECT_EQ(dp::count_islands(grid), expected);
}

INSTANTIATE_TEST_SUITE_P(DataFiles, BigIslandTest,
                         ::testing::ValuesIn(find_test_files(DATA_DIR
                                                             "/big_island")));