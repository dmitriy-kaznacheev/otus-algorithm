#pragma once
#include <graph_core/base_graph.h>

namespace graph_core {

// Перечисление множеств
template <typename T>
class EnumerateGraph final : public GraphBase<EnumerateGraph<T>, T, Edge<T>> {
public:
  void add_vertex_impl(const T &v) { vertices_.insert(v); }

  void add_edge_impl(const Edge<T> &edge) {
    auto [from, to] = edge;
    add_vertex_impl(from);
    add_vertex_impl(to);
    edges_.insert({from, to});
  }

  bool has_edge_impl(const T &from, const T &to) const {
    return edges_.count({from, to}) > 0;
  }

  std::vector<T> get_neighbors_impl(const T &v) const {
    std::vector<T> neighbors;
    for (const auto &[from, to] : edges_) {
      if (from == v) {
        neighbors.push_back(to);
      } else if (to == v) {
        neighbors.push_back(from);
      }
    }
    return neighbors;
  }

  size_t vertex_count_impl() const { return vertices_.size(); }

  size_t edge_count_impl() const { return edges_.size(); }

  std::vector<T> get_vertices_impl() const {
    return std::vector<T>(vertices_.begin(), vertices_.end());
  }

  std::vector<Edge<T>> get_edges_impl() const {
    return std::vector<Edge<T>>(edges_.begin(), edges_.end());
  }

private:
  std::unordered_set<T> vertices_;
  std::unordered_set<Edge<T>, EdgeHash<T>> edges_;
};

} // namespace graph_core
