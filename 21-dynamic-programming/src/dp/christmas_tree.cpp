#include <algorithm>
#include <dp/christmas_tree.h>

namespace dp {

int max_garland_sum(const std::vector<std::vector<int>> &triangle) {
  if (triangle.empty()) {
    return 0;
  }

  int n = triangle.size();

  std::vector<std::vector<int>> dp = triangle;
  for (int i = n - 2; i >= 0; --i) {
    for (int j = 0; j <= i; ++j) {
      dp[i][j] += std::max(dp[i + 1][j], dp[i + 1][j + 1]);
    }
  }
  return dp[0][0];
}

} // namespace dp
