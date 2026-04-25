#pragma once
#include <graph_core/base_graph.h>

namespace graph_core {

// Матрица инцидентности
template <typename T>
class IncidenceMatrixGraph final
    : public GraphBase<IncidenceMatrixGraph<T>, T, Edge<T>> {
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
    if (const auto &[from, to] = edge; has_edge_impl(from, to)) {
      return;
    }

    auto [from, to] = edge;
    add_vertex_impl(from);
    add_vertex_impl(to);

    edges_.push_back(edge);
    resize_matrix();

    size_t from_idx = index_[from];
    size_t to_idx = index_[to];
    size_t edge_idx = edges_.size() - 1;

    matrix_[from_idx][edge_idx] = 1; // исходящее ребро
    matrix_[to_idx][edge_idx] = -1; // входящее ребро (для орграфа)
  }

  bool has_edge_impl(const T &from, const T &to) const {
    if (!has_vertex(from) || !has_vertex(to)) {
      return false;
    }

    Edge<T> target{from, to};
    auto it = std::find(edges_.begin(), edges_.end(), target);
    return (it != edges_.end());
  }

  std::vector<T> get_neighbors_impl(const T &v) const {
    if (!has_vertex(v)) {
      return {};
    }

    std::vector<T> neighbors;
    size_t v_idx = index_.at(v);
    for (size_t e_idx = 0; e_idx != edges_.size(); ++e_idx) {
      if (matrix_[v_idx][e_idx] == 1) { // исходящее ребро
        const auto &[_, to] = edges_[e_idx];
        neighbors.push_back(to);
      }
    }
    return neighbors;
  }

  size_t vertex_count_impl() const { return vertices_.size(); }

  size_t edge_count_impl() const { return edges_.size(); }

  std::vector<T> get_vertices_impl() const { return vertices_; }

  std::vector<Edge<T>> get_edges_impl() const { return edges_; }

private:
  bool has_vertex(const T &v) const { return index_.find(v) != index_.end(); }

  void resize_matrix() {
    size_t v_size = vertices_.size();
    if (matrix_.size() < v_size) {
      if (matrix_.capacity() < v_size) {
        matrix_.reserve(v_size * 2);
      }
      matrix_.resize(v_size);
    }

    size_t e_size = edges_.size();
    if (!matrix_.empty() && matrix_[0].size() < e_size) {
      for (auto &row : matrix_) {
        if (row.capacity() < e_size) {
          row.reserve(e_size * 2);
        }
        row.resize(e_size, 0);
      }
    }
  }

private:
  std::vector<T> vertices_;
  std::vector<Edge<T>> edges_;
  std::vector<std::vector<int>> matrix_;
  std::unordered_map<T, size_t> index_; // вершина -> index;
};

} // namespace graph_core
