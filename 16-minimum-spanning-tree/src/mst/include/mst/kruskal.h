#pragma once
#include <algorithm>
#include <mst/core.h>

namespace mst {

// is_mst: true - выбрасывает исключение для несвязных графов
//         false - возвращает минимальный остовный лес (MSF)

template <typename T>
inline std::vector<Edge<T>> kruskal(const Graph<T> &graph, bool is_mst = true) {
  auto vertex_count = graph.get_vertex_count();
  if (vertex_count == 0) {
    return {};
  }

  auto edges = graph.get_edges();
  std::sort(edges.begin(), edges.end(),
            [](const Edge<T> &lhs, const Edge<T> &rhs) {
              return lhs.weight < rhs.weight;
            });

  DSU dsu(graph.get_vertex_count());
  std::vector<Edge<T>> result;

  if (is_mst) {
    result.reserve(vertex_count - 1);
  }

  for (const auto &e : edges) {
    if (dsu.unite(e.from, e.to)) {
      result.push_back(e);

      if (is_mst && (result.size() == (vertex_count - 1))) {
        // ранний выход (для MST) после нахождения V-1 рёбер
        break;
      }
    }
  }

  // проверить на связность
  if (is_mst && (result.size() != (vertex_count - 1))) {
    throw std::runtime_error("graph is not connected");
  }

  return result;
}

} // namespace mst