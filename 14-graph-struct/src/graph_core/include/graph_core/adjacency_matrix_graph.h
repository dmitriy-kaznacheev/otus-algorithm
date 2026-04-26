#pragma once
#include <graph_core/base_graph.h>
#include <numeric>

namespace graph_core {

template <typename T>
class AdjacencyMatrixGraph final
    : public GraphBase<AdjacencyMatrixGraph<T>, T, Edge<T>> {
public:
  void add_vertex_impl(const T &v) {
    if (has_vertex(v)) {
      return;
    }

    index_[v] = vertices_.size();
    vertices_.push_back(v);
    resize_matrix();
  }

  void add_edge_impl(const Edge<T> &edge) {
    auto [from, to] = edge;
    // TODO: в такой реализации петлю создать нельзя
    add_vertex_impl(from);
    add_vertex_impl(to);
    size_t from_idx = index_[from];
    size_t to_idx = index_[to];
    matrix_[from_idx][to_idx] = (from_idx == to_idx) ? 2 : 1;
  }

  bool has_edge_impl(const T &from, const T &to) const {
    if (!has_vertex(from) || !has_vertex(to)) {
      return false;
    }

    size_t from_idx = index_.at(from);
    size_t to_idx = index_.at(to);
    return (matrix_[from_idx][to_idx] != 0);
  }

  std::vector<T> get_neighbors_impl(const T &v) const {
    if (!has_vertex(v)) {
      return {};
    }

    std::vector<T> neighbors;
    size_t v_idx = index_.at(v);
    for (size_t i = 0; i != vertices_.size(); ++i) {
      if (matrix_[v_idx][i] != 0) {
        neighbors.push_back(vertices_[i]);
      }
    }
    return neighbors;
  }

  size_t vertex_count_impl() const { return vertices_.size(); }

  size_t edge_count_impl() const {
    size_t count = std::accumulate(
        matrix_.begin(), matrix_.end(), 0, [](int sum, const auto &row) {
          return sum + std::count_if(row.begin(), row.end(),
                                     [](int edge) { return edge != 0; });
        });
    return count;
  }

  std::vector<T> get_vertices_impl() const { return vertices_; }

  std::vector<Edge<T>> get_edges_impl() const {
    std::vector<Edge<T>> edges;
    const size_t sz = matrix_.size();
    for (size_t i = 0; i != sz; ++i) {
      for (size_t j = 0; j != sz; ++j) {
        if (matrix_[i][j] != 0) {
          edges.emplace_back(vertices_[i], vertices_[j]);
        }
      }
    }
    return edges;
  }

private:
  bool has_vertex(const T &v) const { return index_.find(v) != index_.end(); }

  void resize_matrix() {
    const size_t sz = vertices_.size();
    matrix_.resize(sz);
    for (auto &row : matrix_) {
      row.resize(sz, 0);
    }
  }

private:
  std::vector<T> vertices_;
  std::vector<std::vector<int>> matrix_;
  std::unordered_map<T, size_t> index_; // вершина -> index
};

} // namespace graph_core
