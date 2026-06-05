#include <dp/big_island.h>
#include <queue>
#include <utility>

namespace dp {

int count_islands(const std::vector<std::vector<int>> &grid) {
  if (grid.empty()) {
    return 0;
  }

  int n = grid.size();
  auto visited = grid; // копия для модификации
  int count = 0;

  // направления
  const int dx[] = {-1, 1, 0, 0};
  const int dy[] = {0, 0, -1, 1};

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (visited[i][j] == 1) {
        ++count; // начало нового острова

        // BFS затопление
        std::queue<std::pair<int, int>> q;
        q.push({i, j});
        visited[i][j] = 0;

        while (!q.empty()) {
          auto [x, y] = q.front();
          q.pop();

          for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if ((nx >= 0) && (nx < n) && (ny >= 0) && (ny < n) &&
                (visited[nx][ny] == 1)) {
              visited[nx][ny] = 0;
              q.push({nx, ny});
            }
          }
        }
      }
    }
  }

  return count;
}

} // namespace dp