#pragma once
#include <graph_core/base_graph.h>

namespace graph_core {

// Векторы смежности
template <typename T>
class AdjacencyVectorGraph final
    : public GraphBase<AdjacencyVectorGraph<T>, T, Edge<T>> {
public:
  void add_vertex_impl(const T &v) {
    if (has_vertex(v)) {
      return;
    }

    index_[v] = vertices_.size();
    vertices_.push_back(v);
    vectors_.push_back({});
  }

  void add_edge_impl(const Edge<T> &edge) {
    if (const auto &[from, to] = edge; has_edge_impl(from, to)) {
      return;
    }

    auto [from, to] = edge;
    add_vertex_impl(from);
    add_vertex_impl(to);
    size_t from_idx = index_[from];
    vectors_[from_idx].push_back(to);
  }

  bool has_edge_impl(const T &from, const T &to) const {
    if (!has_vertex(from) || !has_vertex(to)) {
      return false;
    }

    size_t idx = index_.at(from);
    auto it = std::find(vectors_[idx].begin(), vectors_[idx].end(), to);
    return (it != vectors_[idx].end());
  }

  std::vector<T> get_neighbors_impl(const T &v) const {
    if (!has_vertex(v)) {
      return {};
    }

    size_t idx = index_.at(v);
    return vectors_[idx];
  }

  size_t vertex_count_impl() const { return vertices_.size(); }

  size_t edge_count_impl() const {
    size_t count = 0;
    for (const auto &neighbors : vectors_) {
      count += neighbors.size();
    }
    return count;
  }

  std::vector<T> get_vertices_impl() const { return vertices_; }

  std::vector<Edge<T>> get_edges_impl() const {
    std::vector<Edge<T>> edges;
    for (size_t i = 0; i != vectors_.size(); ++i) {
      for (size_t j = 0; j != vectors_[i].size(); ++j) {
        edges.emplace_back(vertices_[i], vectors_[i][j]);
      }
    }
    return edges;
  }

private:
  bool has_vertex(const T &v) const { return index_.find(v) != index_.end(); }

private:
  std::vector<T> vertices_;
  std::vector<std::vector<T>> vectors_;
  std::unordered_map<T, size_t> index_; // вершина -> index;
};

} // namespace graph_core
