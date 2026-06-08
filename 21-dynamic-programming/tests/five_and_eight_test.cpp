#include "utils.h"
#include <dp/five_and_eight.h>
#include <gtest/gtest.h>

TEST(manual_five_and_eight_test, N1) {
  EXPECT_EQ(dp::count_five_eight_numbers(1), 2);
}

TEST(manual_five_and_eight_test, N2) {
  EXPECT_EQ(dp::count_five_eight_numbers(2), 4);
}

TEST(manual_five_and_eight_test, N3) {
  EXPECT_EQ(dp::count_five_eight_numbers(3), 6);
}

TEST(manual_five_and_eight_test, N4) {
  EXPECT_EQ(dp::count_five_eight_numbers(4), 10);
}

TEST(manual_five_and_eight_test, N5) {
  EXPECT_EQ(dp::count_five_eight_numbers(5), 16);
}

TEST(manual_five_and_eight_test, N_large) {
  EXPECT_GT(dp::count_five_eight_numbers(50), 0);
  EXPECT_NO_THROW(dp::count_five_eight_numbers(88));
}

class FiveAndEightTest
    : public ::testing::TestWithParam<std::pair<std::string, std::string>> {};

TEST_P(FiveAndEightTest, file) {
  auto [input_file, output_file] = GetParam();
  std::string input = read_file(input_file);
  std::string output = read_file(output_file);

  auto N = std::stoi(input);
  auto expected = std::stol(output);

  EXPECT_EQ(dp::count_five_eight_numbers(N), expected);
}

INSTANTIATE_TEST_SUITE_P(
    DataFiles, FiveAndEightTest,
    ::testing::ValuesIn(find_test_files(DATA_DIR "/five_and_eight")));