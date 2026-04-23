#pragma once
#include <algorithm>
#include <iostream>
#include <list>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace graph_core {

template <typename T> using Edge = std::pair<T, T>;

template <typename T> bool operator==(const Edge<T> &lhs, const Edge<T> &rhs) {
  return (lhs.first == rhs.first) && (lhs.second == rhs.second);
}

template <typename T> struct EdgeHash final {
  std::size_t operator()(const Edge<T> &e) const {
    auto h1 = std::hash<T>{}(e.first);
    auto h2 = std::hash<T>{}(e.second);
    return h1 ^ (h2 << 1);
  }
};

// Базовый CRTP-интерфейс для графа
template <typename Derived, typename Vertex, typename Edge> class GraphBase {
public:
  void add_vertex(const Vertex &v) {
    static_cast<Derived *>(this)->add_vertex_impl(v);
  }

  void add_edge(const Edge &e) {
    static_cast<Derived *>(this)->add_edge_impl(e);
  }

  bool has_edge(const Vertex &from, const Vertex &to) const {
    return static_cast<const Derived *>(this)->has_edge_impl(from, to);
  }

  std::vector<Vertex> get_neighbors(const Vertex &v) const {
    return static_cast<const Derived *>(this)->get_neighbors_impl(v);
  }

  size_t vertex_count() const {
    return static_cast<const Derived *>(this)->vertex_count_impl();
  }

  size_t edge_count() const {
    return static_cast<const Derived *>(this)->edge_count_impl();
  }

  std::vector<Vertex> get_vertices() const {
    return static_cast<const Derived *>(this)->get_vertices_impl();
  }

  std::vector<Edge> get_edges() const {
    return static_cast<const Derived *>(this)->get_edges_impl();
  }
};

} // namespace graph_core