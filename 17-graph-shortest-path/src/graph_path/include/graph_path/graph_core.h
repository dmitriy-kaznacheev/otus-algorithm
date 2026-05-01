#pragma once
#include <list>
#include <stdexcept>
#include <vector>

namespace graph_path {

template <typename T> class Graph final {
public:
  struct Edge final {
    size_t from;
    size_t to;
    T weight;
  };

  Graph(size_t vertices) : vertices_{vertices}, adj_(vertices) {}

  void add_edge(size_t from, size_t to, T weight) {
    if ((from >= vertices_) || (to >= vertices_)) {
      throw std::out_of_range("vertex index out of bounds");
    }
    Edge edge{from, to, weight};
    adj_[from].push_back(edge);
    all_edges_.push_back(edge);
  }

  void add_undirected_edge(size_t from, size_t to, T weight) {
    add_edge(from, to, weight);
    add_edge(to, from, weight); // обратное ребро
  }

  size_t get_vertices() const { return vertices_; }
  const std::vector<std::list<Edge>> &get_adj() const & { return adj_; }
  const std::vector<Edge> &get_all_edges() const & { return all_edges_; }

private:
  size_t vertices_;
  std::vector<std::list<Edge>> adj_; // для Дейкстры (список смежности)
  std::vector<Edge> all_edges_; // для Белмана-Форда (плоский вектор ребер)
};

} // namespace graph_path
