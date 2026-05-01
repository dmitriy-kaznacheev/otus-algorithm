#pragma once
#include <stdexcept>
#include <vector>

namespace graph_utils {

template <typename T> class AdjacencyMatrix final {
public:
  explicit AdjacencyMatrix(size_t vertex_count)
      : size_{vertex_count},
        matrix_{vertex_count, std::vector<T>(vertex_count, 0)} {}

  void add_edge(size_t from_vertex, size_t to_vertex, T weight = 1) {
    // TODO: вес "0" -- отсутсвие ребра (возможно это не правильно)
    if ((from_vertex >= size_) || (to_vertex >= size_)) {
      throw std::out_of_range("vertex index out of bounds");
    }
    matrix_[from_vertex][to_vertex] = weight;
  }

  size_t get_size() const { return size_; }

  T get_weight(size_t from_vertex, size_t to_vertex) const {
    return matrix_[from_vertex][to_vertex];
  }

  std::vector<int> get_in_degrees() const {
    // TODO: пересчитывается каждый раз (кэшировать)
    std::vector<int> in_degrees(size_, 0);
    for (size_t col = 0; col != size_; ++col) {
      for (size_t row = 0; row != size_; ++row) {
        if (matrix_[row][col] > 0) {
          ++in_degrees[col];
        }
      }
    }
    return in_degrees;
  }

private:
  std::vector<std::vector<T>> matrix_;
  size_t size_;
};

} // namespace graph_utils
