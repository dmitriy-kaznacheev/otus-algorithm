#include <chrono>
#include <dp/barn.h>
#include <gtest/gtest.h>
#include <random>

using Grid = std::vector<std::vector<int>>;
using Obstacles = std::vector<std::pair<int, int>>;
using Lengths = std::vector<int>;

//--- ЭТАП 1: маленький сарай (брутфорс) --------------------------------------

TEST(small_barn_test, simple) {
  const auto grid = Grid{{0, 1, 0}, {0, 0, 0}, {0, 0, 1}};
  EXPECT_EQ(dp::max_barn_area_bruteforce(grid), 4);
}

TEST(small_barn_test, empty) {
  const auto grid = Grid{{0, 0}, {0, 0}};
  EXPECT_EQ(dp::max_barn_area_bruteforce(grid), 4);
}

TEST(small_barn_test, center_empty) {
  const auto grid =
      Grid{{1, 1, 1, 1}, {1, 0, 0, 1}, {1, 0, 0, 1}, {1, 1, 1, 1}};
  EXPECT_EQ(dp::max_barn_area_bruteforce(grid), 4);
}

TEST(small_barn_test, all_filled) {
  const auto grid = Grid{{1, 1}, {1, 1}};
  EXPECT_EQ(dp::max_barn_area_bruteforce(grid), 0);
}

TEST(small_barn_test, single_empty_cell) {
  const auto grid = Grid{{1, 0, 1}, {1, 1, 1}};
  EXPECT_EQ(dp::max_barn_area_bruteforce(grid), 1);
}

TEST(small_barn_test, empty_grid) {
  const auto grid = Grid{};
  EXPECT_EQ(dp::max_barn_area_bruteforce(grid), 0);
}

TEST(small_barn_test, single_row) {
  const auto grid = Grid{{0, 0, 1, 0, 0}};
  EXPECT_EQ(dp::max_barn_area_bruteforce(grid), 2);
}

TEST(small_barn_test, single_column) {
  const auto grid = Grid{{1}, {0}, {0}, {1}, {0}};
  EXPECT_EQ(dp::max_barn_area_bruteforce(grid), 2);
}

//--- ЭТАП 2: длина сарая -----------------------------------------------------

TEST(barn_length_test, simple) {
  const auto n{3}, m{4};
  const auto blocked = Obstacles{{0, 1}, {2, 2}};

  const auto length = dp::compute_barn_length(n, m, blocked);
  const auto expected = Grid{{1, 0, 1, 1}, {2, 1, 2, 2}, {3, 2, 0, 3}};

  EXPECT_EQ(length, expected);
}

TEST(barn_length_test, no_obstacles) {
  const auto n{3}, m{3};
  const auto blocked = Obstacles{};

  const auto length = dp::compute_barn_length(n, m, blocked);
  const auto expected = Grid{{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};

  EXPECT_EQ(length, expected);
}

TEST(barn_length_test, no_free) {
  const auto n{2}, m{2};
  const auto blocked = Obstacles{{0, 0}, {0, 1}, {1, 0}, {1, 1}};

  const auto length = dp::compute_barn_length(n, m, blocked);
  const auto expected = Grid{{0, 0}, {0, 0}};

  EXPECT_EQ(length, expected);
}

TEST(barn_length_test, single_column) {
  const auto n{4}, m{1};
  const auto blocked = Obstacles{{1, 0}};

  const auto length = dp::compute_barn_length(n, m, blocked);
  const auto expected = Grid{{1}, {0}, {1}, {2}};

  EXPECT_EQ(length, expected);
}

TEST(barn_length_test, first_row_obstacle) {
  const auto n{3}, m{3};
  const auto blocked = Obstacles{{0, 0}, {0, 1}, {0, 2}};

  const auto length = dp::compute_barn_length(n, m, blocked);
  const auto expected = Grid{{0, 0, 0}, {1, 1, 1}, {2, 2, 2}};

  EXPECT_EQ(length, expected);
}

TEST(barn_length_test, scattered_obstacles) {
  const auto n{4}, m{3};
  const auto blocked = Obstacles{{0, 0}, {2, 1}};

  const auto length = dp::compute_barn_length(n, m, blocked);
  const auto expected = Grid{{0, 1, 1}, {1, 2, 2}, {2, 0, 3}, {3, 1, 4}};

  EXPECT_EQ(length, expected);
}

//--- ЭТАП 3: ширина сарая ----------------------------------------------------

TEST(barn_width_test, example_from_task) {
  const auto lengths = Lengths{2, 1, 5, 6, 2, 3};

  const auto [L, R] = dp::compute_barn_width(lengths);
  const auto expected_L = Lengths{0, 0, 2, 3, 2, 5};
  const auto expected_R = Lengths{0, 5, 3, 3, 5, 5};

  EXPECT_EQ(L, expected_L);
  EXPECT_EQ(R, expected_R);
}

TEST(barn_width_test, increasing_sequence) {
  const auto lengths = Lengths{1, 2, 3, 4, 5};

  const auto [L, R] = dp::compute_barn_width(lengths);
  const auto expected_L = Lengths{0, 1, 2, 3, 4};
  const auto expected_R = Lengths{4, 4, 4, 4, 4};

  EXPECT_EQ(L, expected_L);
  EXPECT_EQ(R, expected_R);
}

TEST(barn_width_test, secreasing_sequence) {
  const auto lengths = Lengths{5, 4, 3, 2, 1};

  const auto [L, R] = dp::compute_barn_width(lengths);
  const auto expected_L = Lengths{0, 0, 0, 0, 0};
  const auto expected_R = Lengths{0, 1, 2, 3, 4};

  EXPECT_EQ(L, expected_L);
  EXPECT_EQ(R, expected_R);
}

TEST(barn_width_test, all_equal) {
  const auto lengths = Lengths{3, 3, 3, 3};

  const auto [L, R] = dp::compute_barn_width(lengths);
  const auto expected_L = Lengths{0, 0, 0, 0};
  const auto expected_R = Lengths{3, 3, 3, 3};

  EXPECT_EQ(L, expected_L);
  EXPECT_EQ(R, expected_R);
}

TEST(barn_width_test, single_element) {
  const auto lengths = Lengths{7};

  const auto [L, R] = dp::compute_barn_width(lengths);
  EXPECT_EQ(L.size(), 1);
  EXPECT_EQ(R.size(), 1);
  EXPECT_EQ(L[0], 0);
  EXPECT_EQ(R[0], 0);
}

TEST(barn_width_test, empty_array) {
  const auto lengths = Lengths{};

  const auto [L, R] = dp::compute_barn_width(lengths);
  EXPECT_TRUE(L.empty());
  EXPECT_TRUE(R.empty());
}

TEST(barn_width_test, min_in_middle) {
  const auto lengths = Lengths{4, 1, 4};

  const auto [L, R] = dp::compute_barn_width(lengths);
  const auto expected_L = Lengths{0, 0, 2};
  const auto expected_R = Lengths{0, 2, 2};

  EXPECT_EQ(L, expected_L);
  EXPECT_EQ(R, expected_R);
}

TEST(barn_width_test, max_in_middle) {
  const auto lengths = Lengths{1, 4, 1};

  const auto [L, R] = dp::compute_barn_width(lengths);
  const auto expected_L = Lengths{0, 1, 0};
  const auto expected_R = Lengths{2, 1, 2};

  EXPECT_EQ(L, expected_L);
  EXPECT_EQ(R, expected_R);
}

TEST(barn_width_test, every_other_max) {
  const auto lengths = Lengths{1, 5, 1, 5, 1};

  const auto [L, R] = dp::compute_barn_width(lengths);
  const auto expected_L = Lengths{0, 1, 0, 3, 0};
  const auto expected_R = Lengths{4, 1, 4, 3, 4};

  EXPECT_EQ(L, expected_L);
  EXPECT_EQ(R, expected_R);
}

//--- ЭТАП 4: Большой сарай (оптимальный алгоритм) ----------------------------

TEST(big_barn_test, example_from_task) {
  const auto n{4}, m{5};
  const auto blocked = Obstacles{{0, 1}, {0, 4}, {1, 1}, {2, 3}, {3, 0}};
  EXPECT_EQ(dp::max_barn_area(n, m, blocked), 4);
}

TEST(big_barn_test, no_obstacles) {
  const auto n{3}, m{4};
  const auto blocked = Obstacles{};
  EXPECT_EQ(dp::max_barn_area(n, m, blocked), 12);
}

TEST(big_barn_test, diagonal_obstacles) {
  const auto n{3}, m{4};
  const auto blocked = Obstacles{{0, 0}, {1, 1}, {2, 2}};
  EXPECT_EQ(dp::max_barn_area(n, m, blocked), 4);
}

TEST(big_barn_test, single_empty_cell) {
  const auto n{1}, m{1};
  const auto blocked = Obstacles{};
  EXPECT_EQ(dp::max_barn_area(n, m, blocked), 1);
}

TEST(big_barn_test, single_occupied_cell) {
  const auto n{1}, m{1};
  const auto blocked = Obstacles{{0, 0}};
  EXPECT_EQ(dp::max_barn_area(n, m, blocked), 0);
}

TEST(big_barn_test, large_grid_with_one_obstacle) {
  const auto n{10}, m{10};
  const auto blocked = Obstacles{{5, 5}};
  EXPECT_EQ(dp::max_barn_area(n, m, blocked), 50);
}

TEST(big_barn_test, vertical_stripe) {
  const auto n{5}, m{1};
  const auto blocked = Obstacles{{2, 0}};
  EXPECT_EQ(dp::max_barn_area(n, m, blocked), 2);
}

TEST(big_barn_test, cross_obstacles) {
  const auto n{5}, m{5};
  auto blocked = Obstacles{};

  for (int i = 0; i < 5; ++i) {
    blocked.push_back({2, i}); // горизонталь
    blocked.push_back({i, 2}); // вертикаль
  }

  EXPECT_EQ(dp::max_barn_area(n, m, blocked), 4);
}

TEST(big_barn_test, all_occupied) {
  const auto n{3}, m{3};
  auto blocked = Obstacles{};

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      blocked.push_back({i, j});
    }
  }

  EXPECT_EQ(dp::max_barn_area(n, m, blocked), 0);
}

TEST(big_barn_test, horizontal_obstacle_line) {
  const auto n{4}, m{4};
  const auto blocked = Obstacles{{1, 0}, {1, 1}, {1, 2}, {1, 3}};
  EXPECT_EQ(dp::max_barn_area(n, m, blocked), 8);
}

TEST(big_barn_test, vertical_obstacle_line) {
  const auto n{4}, m{4};
  const auto blocked = Obstacles{{0, 1}, {1, 1}, {2, 1}, {3, 1}};
  EXPECT_EQ(dp::max_barn_area(n, m, blocked), 8);
}

TEST(big_barn_test, chess_pattern) {
  const auto n{4}, m{4};
  auto blocked = Obstacles{};

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if ((i + j) % 2 == 0) {
        blocked.push_back({i, j});
      }
    }
  }
  EXPECT_EQ(dp::max_barn_area(n, m, blocked), 1);
}

TEST(big_barn_test, rectangle_in_corner) {
  const auto n{3}, m{4};
  const auto blocked =
      Obstacles{{0, 3}, {1, 3}, {2, 0}, {2, 1}, {2, 2}, {2, 3}};
  EXPECT_EQ(dp::max_barn_area(n, m, blocked), 6);
}

TEST(big_barn_test, wide_field) {
  const auto n{3}, m{10};
  const auto blocked = Obstacles{{1, 5}};
  EXPECT_EQ(dp::max_barn_area(n, m, blocked), 15);
}

TEST(big_barn_test, tall_field) {
  const auto n{10}, m{3};
  const auto blocked = Obstacles{{5, 1}};
  EXPECT_EQ(dp::max_barn_area(n, m, blocked), 15);
}

TEST(big_barn_test, multiple_scattered_obstacles) {
  const auto n{5}, m{5};
  const auto blocked = Obstacles{{0, 0}, {0, 4}, {4, 0}, {4, 4}, {2, 2}};
  EXPECT_GT(dp::max_barn_area(n, m, blocked), 0);
  EXPECT_LE(dp::max_barn_area(n, m, blocked), 25);
}

TEST(big_barn_test, single_row) {
  const auto n{1}, m{10};
  const auto blocked = Obstacles{{0, 3}, {0, 7}};
  EXPECT_EQ(dp::max_barn_area(n, m, blocked), 3);
}

TEST(big_barn_test, single_column) {
  const auto n{10}, m{1};
  const auto blocked = Obstacles{{3, 0}, {7, 0}};
  EXPECT_EQ(dp::max_barn_area(n, m, blocked), 3);
}

TEST(big_barn_test, border_obstacles) {
  const auto n{5}, m{5};
  auto blocked = Obstacles{};

  for (int i = 0; i < n; ++i) {
    blocked.push_back({i, 0});
    blocked.push_back({i, m - 1});
  }
  for (int j = 1; j < m - 1; ++j) {
    blocked.push_back({0, j});
    blocked.push_back({n - 1, j});
  }

  EXPECT_EQ(dp::max_barn_area(n, m, blocked), 9);
}

TEST(big_barn_test, complex_case) {
  const auto n{6}, m{6};
  const auto blocked = Obstacles{{0, 2}, {1, 2}, {2, 2}, {3, 0}, {3, 1}, {4, 0},
                                 {4, 1}, {3, 4}, {3, 5}, {4, 4}, {4, 5}};
  EXPECT_EQ(dp::max_barn_area(n, m, blocked), 9);
}

//--- обработка ошибок ---

TEST(big_barn_test, invalid_coordinates) {
  const auto n{3}, m{3};
  const auto blocked = Obstacles{{5, 5}};
  EXPECT_THROW(dp::max_barn_area(n, m, blocked), std::out_of_range);
}

TEST(big_barn_test, negative_coordinates) {
  const auto n{3}, m{3};
  const auto blocked = Obstacles{{-1, 0}};
  EXPECT_THROW(dp::max_barn_area(n, m, blocked), std::out_of_range);
}

TEST(big_barn_test, duplicate_obstacles) {
  const auto n{3}, m{3};
  const auto blocked = Obstacles{{0, 0}, {0, 0}, {1, 1}};
  // не должно падать, результат как для уникальных
  EXPECT_NO_THROW(dp::max_barn_area(n, m, blocked));
}

TEST(big_barn_test, zero_size_grid) {
  const auto n{0}, m{0};
  const auto blocked = Obstacles{};
  EXPECT_EQ(dp::max_barn_area(n, m, blocked), 0);
}

TEST(verification_test, bruteforce_vs_optimal) {
  // маленькие сетки, где брутфорс ещё работает
  for (int n = 1; n <= 5; ++n) {
    for (int m = 1; m <= 5; ++m) {
      auto grid = Grid(n, std::vector<int>(m, 0));
      auto blocked = Obstacles{};

      std::mt19937 rng(n * m);
      std::uniform_int_distribution<int> dist(0, 1);

      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          if (dist(rng)) {
            grid[i][j] = 1;
            blocked.push_back({i, j});
          }
        }
      }

      int brute_result = dp::max_barn_area_bruteforce(grid);
      int optimal_result = dp::max_barn_area(n, m, blocked);

      EXPECT_EQ(brute_result, optimal_result)
          << "Mismatch for grid " << n << "x" << m;
    }
  }
}
