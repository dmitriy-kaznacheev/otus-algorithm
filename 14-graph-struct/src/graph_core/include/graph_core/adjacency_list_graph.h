#pragma once
#include <graph_core/base_graph.h>

namespace graph_core {

// Списки смежности
template <typename T>
class AdjacencyListGraph final
    : public GraphBase<AdjacencyListGraph<T>, T, Edge<T>> {
public:
  void add_vertex_impl(const T &v) {
    if (has_vertex(v)) {
      return;
    }

    lists_[v] = {};
  }

  void add_edge_impl(const Edge<T> &edge) {
    if (const auto &[from, to] = edge; has_edge_impl(from, to)) {
      return;
    }

    auto [from, to] = edge;
    add_vertex_impl(from);
    add_vertex_impl(to);
    lists_[from].push_back(to);
  }

  bool has_edge_impl(const T &from, const T &to) const {
    if (!has_vertex(from) || !has_vertex(to)) {
      return false;
    }

    const auto &neighbors = lists_.at(from);
    auto it = std::find(neighbors.begin(), neighbors.end(), to);
    return (it != neighbors.end());
  }

  std::vector<T> get_neighbors_impl(const T &v) const {
    if (!has_vertex(v)) {
      return {};
    }

    const auto &neighbors = lists_.at(v);
    return std::vector<T>(neighbors.begin(), neighbors.end());
  }

  size_t vertex_count_impl() const { return lists_.size(); }

  size_t edge_count_impl() const {
    size_t count = 0;
    for (const auto &[_, neighbors] : lists_) {
      count += neighbors.size();
    }
    return count;
  }

  std::vector<T> get_vertices_impl() const {
    std::vector<T> vertices(vertex_count_impl());
    std::transform(lists_.begin(), lists_.end(), vertices.begin(),
                   [](const auto &pair) { return pair.first; });
    return vertices;
  }

  std::vector<Edge<T>> get_edges_impl() const {
    std::vector<Edge<T>> edges;
    for (const auto &[from, neighbors] : lists_) {
      for (const auto &to : neighbors) {
        edges.emplace_back(from, to);
      }
    }
    return edges;
  }

private:
  bool has_vertex(const T &v) const { return lists_.count(v) > 0; }

private:
  std::unordered_map<T, std::list<T>> lists_;
};

} // namespace graph_core
