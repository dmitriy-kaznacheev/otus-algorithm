#pragma once
#include <graph_path/graph_core.h>
#include <limits>
#include <queue>

namespace graph_path {

namespace detail {
template <typename T>
inline void check_negative_weights(const Graph<T> &graph) {
  if constexpr (std::is_arithmetic_v<T>) {
    for (const auto &edge : graph.get_all_edges()) {
      if (edge.weight < T{0}) {
        throw std::invalid_argument(
            "Dijkstra's algorithm requires non-negative edge weights");
      }
    }
  }
}
} // namespace detail

template <typename T>
inline std::vector<T> dejkstra(const Graph<T> &graph, size_t start_node) {
  auto vertices = graph.get_vertices();
  if ((start_node < 0) || (start_node >= vertices)) {
    throw std::out_of_range("start node index out of bounds");
  }

  detail::check_negative_weights(graph);

  T inf = std::numeric_limits<T>::max();
  std::vector<T> shortest_dist(vertices, inf);

  using NodeDist = std::pair<T, int>; // {dist, vertex}
  std::priority_queue<NodeDist, std::vector<NodeDist>, std::greater<NodeDist>>
      pq;
  pq.push({0, start_node});

  shortest_dist[start_node] = 0;
  const auto &adj = graph.get_adj();

  while (!pq.empty()) {
    auto [dist, from] = pq.top();
    pq.pop();

    if (dist == inf) {
      continue; // защита от переполнения
    }

    if (dist > shortest_dist[from]) {
      continue; // устаревшие записи
    }

    for (const auto &edge : adj[from]) {
      if (shortest_dist[from] == inf) {
        continue; // защита от переполнения
      }

      T new_dist = dist + edge.weight;
      if (new_dist < shortest_dist[edge.to]) {
        shortest_dist[edge.to] = new_dist;
        pq.push({new_dist, edge.to});
      }
    }
  }
  return shortest_dist;
}

} // namespace graph_path
