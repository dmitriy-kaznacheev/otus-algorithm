#pragma once
#include <graph_core/base_graph.h>

namespace graph_core {

// Массивы смежности (упрощённая версия для фиксированного числа вершин)
template <typename T, size_t MaxVertices = 100>
class AdjacencyArrayGraph final
    : public GraphBase<AdjacencyArrayGraph<T, MaxVertices>, T, Edge<T>> {

public:
  void add_vertex_impl(const T &v) {
    if (has_vertex(v) || exceeds_vertex_limit()) {
      return;
    }

    index_[v] = vcount_;
    vertices_[vcount_++] = v;
  }

  void add_edge_impl(const Edge<T> &edge) {
    if (const auto &[from, to] = edge; has_edge_impl(from, to)) {
      return;
    }

    auto [from, to] = edge;
    add_vertex_impl(from);
    add_vertex_impl(to);
    size_t from_idx = index_[from];
    arrays_[from_idx].push_back(to);
  }

  bool has_edge_impl(const T &from, const T &to) const {
    if (!has_vertex(from) || !has_vertex(to)) {
      return false;
    }

    size_t idx = index_.at(from);
    auto it = std::find(arrays_[idx].begin(), arrays_[idx].end(), to);
    return (it != arrays_[idx].end());
  }

  std::vector<T> get_neighbors_impl(const T &v) const {
    if (!has_vertex(v)) {
      return {};
    }

    size_t idx = index_.at(v);
    return arrays_[idx];
  }

  size_t vertex_count_impl() const { return vcount_; }

  size_t edge_count_impl() const {
    size_t count = 0;
    for (size_t i = 0; i != vcount_; ++i) {
      count += arrays_[i].size();
    }
    return count;
  }

  std::vector<T> get_vertices_impl() const {
    std::vector<T> vertices(vcount_);
    std::copy_n(vertices_.begin(), vcount_, vertices.begin());
    return vertices;
  }

  std::vector<Edge<T>> get_edges_impl() const {
    std::vector<Edge<T>> edges;
    for (size_t i = 0; i != vcount_; ++i) {
      for (const auto &neighbor : arrays_[i]) {
        edges.emplace_back(vertices_[i], neighbor);
      }
    }
    return edges;
  }

private:
  bool has_vertex(const T &v) const { return index_.find(v) != index_.end(); }
  bool exceeds_vertex_limit() const { return MaxVertices < vcount_; }

private:
  size_t vcount_{0};
  std::array<T, MaxVertices> vertices_;
  std::array<std::vector<T>, MaxVertices> arrays_;
  std::unordered_map<T, size_t> index_; // вершина -> index;
};

} // namespace graph_core
