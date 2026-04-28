#pragma once
#include <algorithm>
#include <mst/core.h>

namespace mst {

template <typename T>
inline std::vector<Edge<T>> kruskal(const Graph<T> &graph) {
  if (graph.get_vertex_count() == 0) {
    return {};
  }

  auto edges = graph.get_edges();
  std::sort(edges.begin(), edges.end(),
            [](const Edge<T> &lhs, const Edge<T> &rhs) {
              return lhs.weight < rhs.weight;
            });

  DSU dsu(graph.get_vertex_count());

  int components = graph.get_vertex_count();
  std::vector<Edge<T>> result;
  for (const auto &e : edges) {
    if (dsu.unite(e.from, e.to)) {
      result.push_back(e);
      --components;
    }
  }

  // проверить на связность
  if (components > 1) {
    throw std::runtime_error("graph is not connected");
  }

  return result;
}

} // namespace mst