#pragma once
#include <numeric>
#include <stdexcept>
#include <vector>

namespace mst {

template <typename T> struct Edge {
  size_t from, to;
  T weight;
  bool operator<(const Edge &rhs) const { return weight < rhs.weight; }
};

template <typename T> class Graph {
public:
  Graph(size_t vertex_count) : vcount_{vertex_count} {}
  void add_edge(size_t from_vertex, size_t to_vertex, T weight = 1) {
    if (from_vertex >= vcount_ || to_vertex >= vcount_) {
      throw std::out_of_range("vertex index out of bounds");
    }
    if (weight < 0) {
      throw std::invalid_argument("edge weight must be non-negative");
    }
    edges_.push_back({from_vertex, to_vertex, weight});
  }
  std::vector<std::vector<std::pair<size_t, T>>> get_adjacency() const {
    std::vector<std::vector<std::pair<size_t, T>>> adj(vcount_);
    for (const auto &e : edges_) {
      adj[e.from].push_back({e.to, e.weight});
      adj[e.to].push_back({e.from, e.weight});
    }
    return adj;
  }
  std::vector<Edge<T>> get_edges() const { return edges_; }
  size_t get_vertex_count() const { return vcount_; }

private:
  std::vector<Edge<T>> edges_;
  size_t vcount_;
};

// DSU (Disjoint Set Union - Система Непересекающихся Множеств)
struct DSU {
  std::vector<size_t> parent, rank;

  DSU(size_t n) : parent(n), rank(n, 0) {
    std::iota(parent.begin(), parent.end(), 0);
  }
  size_t find(size_t i) {
    if (parent[i] == i) {
      return i;
    }
    parent[i] = find(parent[i]);
    return parent[i];
  }

  bool unite(size_t i, size_t j) {
    size_t root_i = find(i);
    size_t root_j = find(j);
    if (root_i == root_j) {
      return false;
    }

    // Union by rank
    if (rank[root_i] < rank[root_j]) {
      parent[root_i] = root_j;
    } else {
      parent[root_j] = root_i;
      if (rank[root_i] == rank[root_j])
        ++rank[root_i];
    }
    return true;
  }
};

} // namespace mst