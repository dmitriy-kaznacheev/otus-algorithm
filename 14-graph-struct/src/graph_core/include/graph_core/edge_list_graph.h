#pragma once
#include <graph_core/base_graph.h>

namespace graph_core {

// Перечень рёбер
template <typename T>
class EdgeListGraph final : public GraphBase<EdgeListGraph<T>, T, Edge<T>> {
public:
  void add_vertex_impl(const T &v) { vertices_.insert(v); }

  void add_edge_impl(const Edge<T> &edge) {
    if (const auto &[from, to] = edge; has_edge_impl(from, to)) {
      return;
    }

    auto [from, to] = edge;
    add_vertex_impl(from);
    add_vertex_impl(to);
    edges_.push_back(edge);
  }

  bool has_edge_impl(const T &from, const T &to) const {
    Edge<T> target{from, to};
    auto it = std::find(edges_.begin(), edges_.end(), target);
    return (it != edges_.end());
  }

  std::vector<T> get_neighbors_impl(const T &v) const {
    std::vector<T> neighbors;
    for (const auto &[from, to] : edges_) {
      if (from == v) {
        neighbors.push_back(to);
      }
    }
    return neighbors;
  }

  size_t vertex_count_impl() const { return vertices_.size(); }

  size_t edge_count_impl() const { return edges_.size(); }

  std::vector<T> get_vertices_impl() const {
    return std::vector<T>(vertices_.begin(), vertices_.end());
  }

  std::vector<Edge<T>> get_edges_impl() const { return edges_; }

private:
  std::vector<Edge<T>> edges_;
  std::unordered_set<T> vertices_;
};

} // namespace graph_core
