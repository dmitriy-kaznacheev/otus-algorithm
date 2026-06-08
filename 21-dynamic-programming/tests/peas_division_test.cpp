#include "utils.h"
#include <dp/peas_division.h>
#include <gtest/gtest.h>

TEST(manual_peas_division_test, simple_fractions) {
  EXPECT_EQ(dp::sum_fractions("1/3+1/3"), "2/3");
  EXPECT_EQ(dp::sum_fractions("1/2+1/3"), "5/6");
}

TEST(manual_peas_division_test, fraction_reduction) {
  EXPECT_EQ(dp::sum_fractions("1/4+1/4"), "1/2");
  EXPECT_EQ(dp::sum_fractions("2/6+1/3"), "2/3");
}

TEST(manual_peas_division_test, large_numbers) {
  EXPECT_EQ(dp::sum_fractions("1/10000+1/10000"), "1/5000");
}

TEST(manual_peas_division_test, sum_one) {
  EXPECT_EQ(dp::sum_fractions("1/2+1/2"), "1/1");
  EXPECT_EQ(dp::sum_fractions("2/5+3/5"), "1/1");
}

TEST(manual_peas_division_test, zero) {
  // хотя по условию числа от 1, но алгоритм должен работать
  EXPECT_EQ(dp::sum_fractions("0/5+1/5"), "1/5");
}

TEST(manual_peas_division_test, invalid_format) {
  EXPECT_THROW(dp::sum_fractions("invalid"), std::invalid_argument);
  EXPECT_THROW(dp::sum_fractions("1/2"), std::invalid_argument);
}

class PeasDivisionTest
    : public ::testing::TestWithParam<std::pair<std::string, std::string>> {};

TEST_P(PeasDivisionTest, file) {
  auto [input_file, output_file] = GetParam();
  std::string input = read_file(input_file);
  std::string expected = read_file(output_file);

  EXPECT_EQ(dp::sum_fractions(input), expected);
}

INSTANTIATE_TEST_SUITE_P(
    DataFiles, PeasDivisionTest,
    ::testing::ValuesIn(find_test_files(DATA_DIR "/peas_division")));