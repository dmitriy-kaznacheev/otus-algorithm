#include <dp/five_and_eight.h>
#include <vector>

namespace dp {

int64_t count_five_eight_numbers(int N) {
  if (N == 0) {
    return 0;
  }

  /**
   * dp[l][last][count] — количество допустимых последовательностей
   *   l=[1..N] — длина
   *   last — последняя цифра (0 => 5, 1 => 8)
   *    count — сколько раз подряд идёт эта последняя цифра (1 или 2)
   **/
  std::vector<std::vector<std::vector<int64_t>>> dp(
      N + 1, std::vector<std::vector<int64_t>>(2, std::vector<int64_t>(3, 0)));

  constexpr int five = 0;
  constexpr int eight = 1;
  constexpr int cnt_1 = 1;
  constexpr int cnt_2 = 2;

  { // базовый случай: длина == 1
    int l = 1;
    dp[l][five][1] = 1;
    dp[l][eight][1] = 1;
  }

  for (int l = 2; l <= N; ++l) {
    dp[l][five][cnt_1] = dp[l - 1][eight][cnt_1] + dp[l - 1][eight][cnt_2];
    dp[l][five][cnt_2] = dp[l - 1][five][cnt_1];

    dp[l][eight][cnt_1] = dp[l - 1][five][cnt_1] + dp[l - 1][five][cnt_2];
    dp[l][eight][cnt_2] = dp[l - 1][eight][cnt_1];
  }

  return dp[N][five][cnt_1] + dp[N][five][cnt_2] + dp[N][eight][cnt_1] +
         dp[N][eight][cnt_2];
}

} // namespace dp
