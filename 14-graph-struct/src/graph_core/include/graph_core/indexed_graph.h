#pragma once
#include <graph_core/base_graph.h>

namespace graph_core {

// Структура с оглавлением
template <typename T>
class IndexedGraph final : public GraphBase<IndexedGraph<T>, T, Edge<T>> {
public:
  void add_vertex_impl(const T &v) {
    if (has_vertex(v)) {
      return;
    }

    vertices_.push_back(v);
    index_[v] = {};
  }

  void add_edge_impl(const Edge<T> &edge) {
    if (const auto &[from, to] = edge; has_edge_impl(from, to)) {
      return;
    }

    auto [from, to] = edge;
    add_vertex_impl(from);
    add_vertex_impl(to);
    edges_.push_back(edge);
    index_[from].push_back(to);
  }

  bool has_edge_impl(const T &from, const T &to) const {
    if (!has_vertex(from) || !has_vertex(to)) {
      return false;
    }

    const auto &neighbors = index_.at(from);
    auto it = std::find(neighbors.begin(), neighbors.end(), to);
    return (it != neighbors.end());
  }

  std::vector<T> get_neighbors_impl(const T &v) const {
    if (!has_vertex(v)) {
      return {};
    }

    const auto &neighbors = index_.at(v);
    return std::vector<T>(neighbors.begin(), neighbors.end());
  }

  size_t vertex_count_impl() const { return vertices_.size(); }

  size_t edge_count_impl() const { return edges_.size(); }

  std::vector<T> get_vertices_impl() const { return vertices_; }

  std::vector<Edge<T>> get_edges_impl() const { return edges_; }

private:
  bool has_vertex(const T &v) const { return index_.count(v) > 0; }

private:
  std::vector<T> vertices_;
  std::vector<Edge<T>> edges_;
  std::unordered_map<T, std::list<T>> index_;
};

} // namespace graph_core
