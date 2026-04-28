#pragma once
#include <mst/core.h>
#include <queue>

namespace mst {

template <typename T>
inline std::vector<Edge<T>> prim(const Graph<T> &graph, size_t start = 0) {
  auto vcount = graph.get_vertex_count();
  if (vcount == 0 || start >= vcount) {
    return {};
  }

  std::vector<Edge<T>> result;
  std::vector<bool> visited(vcount, false);
  auto adj = graph.get_adjacency();

  using WEdge = std::pair<T, std::pair<int, int>>;
  std::priority_queue<WEdge, std::vector<WEdge>, std::greater<WEdge>> pq;

  // начать с вершины "start"
  visited[start] = true;
  for (auto &e : adj[start]) {
    pq.push({e.second, {start, e.first}});
  }

  size_t visited_count = 1;

  while (!pq.empty()) {
    auto top = pq.top();
    pq.pop();

    T w = top.first;
    size_t from = top.second.first;
    size_t to = top.second.second;

    if (visited[to]) {
      continue;
    }

    visited[to] = true;
    ++visited_count;
    result.push_back({from, to, w});

    // добавить рёбра из новой вершины
    for (auto &e : adj[to]) {
      if (!visited[e.first]) {
        pq.push({e.second, {to, e.first}});
      }
    }
  }

  // проверить на связность
  if (visited_count != vcount) {
    throw std::runtime_error("graph is not connected");
  }

  return result;
}

} // namespace mst