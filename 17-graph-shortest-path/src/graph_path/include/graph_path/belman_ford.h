#pragma once
#include <graph_path/graph_core.h>
#include <limits>
#include <optional>

namespace graph_path {

template <typename T>
inline std::optional<std::vector<T>> belman_ford(const Graph<T> &graph,
                                                 size_t start_node) {
  auto vertices = graph.get_vertices();
  if (start_node >= vertices) {
    throw std::out_of_range("start node index out of bounds");
  }

  if (vertices == 0) {
    return std::vector<T>();
  }

  T inf = std::numeric_limits<T>::max();
  std::vector<T> shortest_dist(vertices, inf);
  shortest_dist[start_node] = 0;

  const auto &edges = graph.get_all_edges();

  // распростроение минимальных весов
  for (size_t i = 0; i != (vertices - 1); ++i) {
    bool updated = false;
    for (const auto &edge : edges) {
      if (shortest_dist[edge.from] == inf) {
        continue; // защита от переполнения
      }

      if (edge.weight < 0 && shortest_dist[edge.from] > inf + edge.weight) {
        // защита от переполнения при сложении с отрицательным весом
        continue;
      }

      T new_dist = shortest_dist[edge.from] + edge.weight;
      if (new_dist < shortest_dist[edge.to]) {
        shortest_dist[edge.to] = new_dist;
        updated = true;
      }
    }
    if (!updated) {
      break;
    }
  }

  // проверка на отрицательный цикл
  for (const auto &edge : edges) {
    if (shortest_dist[edge.from] == inf) {
      continue; // защита от переполнения
    }

    T new_dist = shortest_dist[edge.from] + edge.weight;
    if (new_dist < shortest_dist[edge.to]) {
      return std::nullopt; // отрицательный цикл
    }
  }

  return shortest_dist;
}

} // namespace graph_path
