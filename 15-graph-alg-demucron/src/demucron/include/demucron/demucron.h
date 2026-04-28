#pragma once
#include <demucron/adjacency_matrix.h>
#include <vector>

namespace graph_utils {

template <typename T>
std::vector<std::vector<std::size_t>>
demucron_sort(const AdjacencyMatrix<T> &matrix) {
  size_t n = matrix.get_size();
  std::vector<int> in_degrees = matrix.get_in_degrees();
  std::vector<bool> visited(n, false);

  std::vector<std::vector<std::size_t>> levels;

  size_t processed_count = 0;
  while (processed_count < n) {
    std::vector<size_t> current_level;

    // вершины со степенью входа "0", и не посещенные
    for (size_t vertex = 0; vertex != n; ++vertex) {
      if ((in_degrees[vertex] == 0) && !visited[vertex]) {
        current_level.push_back(vertex);
      }
    }

    // если вершин с "0" степенью нет, и не все обрабатано
    if (current_level.empty()) {
      throw std::runtime_error("graph contains cycle!");
    }

    // обновление степеней захода
    for (size_t vertex : current_level) {
      visited[vertex] = true;
      ++processed_count;

      for (size_t neighbor = 0; neighbor < n; ++neighbor) {
        if (matrix.get_weight(vertex, neighbor) > 0) {
          --in_degrees[neighbor];
        }
      }
    }

    levels.push_back(current_level);
  }

  return levels;
};

} // namespace graph_utils
