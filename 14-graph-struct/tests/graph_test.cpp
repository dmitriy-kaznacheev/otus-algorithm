#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

#include <graph_core/adjacency_array_graph.h>
#include <graph_core/adjacency_list_graph.h>
#include <graph_core/adjacency_matrix_graph.h>
#include <graph_core/adjacency_vector_graph.h>
#include <graph_core/edge_list_graph.h>
#include <graph_core/enumerate_graph.h>
#include <graph_core/incidence_matrix_graph.h>
#include <graph_core/indexed_graph.h>
#include <graph_core/vertex_edge_list_graph.h>

using value_type = int;

template <typename T>
bool vectors_equal_unordered(const std::vector<T> &lhs,
                             const std::vector<T> &rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }

  std::vector<T> sorted_lhs = lhs;
  std::vector<T> sorted_rhs = rhs;
  std::sort(sorted_lhs.begin(), sorted_lhs.end());
  std::sort(sorted_rhs.begin(), sorted_rhs.end());
  return sorted_lhs == sorted_rhs;
}

template <typename GraphType> class GraphTest : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

// clang-format off
using GraphTypes = ::testing::Types<
  graph_core::EnumerateGraph<value_type>,
  graph_core::AdjacencyMatrixGraph<value_type>,
  graph_core::IncidenceMatrixGraph<value_type>,
  graph_core::EdgeListGraph<value_type>,
  graph_core::AdjacencyVectorGraph<value_type>,
  graph_core::AdjacencyArrayGraph<value_type, 10>,
  graph_core::AdjacencyListGraph<value_type>,
  graph_core::IndexedGraph<value_type>,
  graph_core::VertexEdgeListGraph<value_type>
>;
// clang-format on

TYPED_TEST_SUITE(GraphTest, GraphTypes);

TYPED_TEST(GraphTest, vertex_operations) {
  TypeParam graph;
  graph.add_vertex(1);
  graph.add_vertex(2);
  graph.add_vertex(3);

  {
    auto expectd = 3;
    auto actual = graph.vertex_count();
    EXPECT_EQ(expectd, actual);
  }

  {
    auto expected = std::vector<value_type>{1, 2, 3};
    auto actual = graph.get_vertices();
    EXPECT_TRUE(vectors_equal_unordered(expected, actual));
  }
}

TYPED_TEST(GraphTest, edge_operations) {
  TypeParam graph;
  graph.add_edge({1, 2});
  graph.add_edge({2, 3});
  graph.add_edge({3, 1});

  EXPECT_EQ(graph.edge_count(), 3);
  EXPECT_TRUE(graph.has_edge(1, 2));
  EXPECT_TRUE(graph.has_edge(2, 3));
  EXPECT_TRUE(graph.has_edge(3, 1));
  EXPECT_FALSE(graph.has_edge(1, 3)); // обратное направление не считается
}

TYPED_TEST(GraphTest, get_neighbors) {
  TypeParam graph;
  graph.add_edge({1, 2});
  graph.add_edge({1, 3});
  graph.add_edge({2, 4});

  {
    auto expected = std::vector<value_type>{2, 3};
    auto actual = graph.get_neighbors(1);
    EXPECT_TRUE(vectors_equal_unordered(expected, actual));
  }

  {
    auto expected = std::vector<value_type>{4};
    auto actual = graph.get_neighbors(2);
    EXPECT_TRUE(vectors_equal_unordered(expected, actual));
  }

  {
    auto actual = graph.get_neighbors(5); // вершиы не существует
    EXPECT_TRUE(actual.empty());
  }
}

TYPED_TEST(GraphTest, get_edges) {
  TypeParam graph;
  graph.add_edge({1, 2});
  graph.add_edge({2, 3});
  graph.add_edge({3, 1});

  using edge_type = graph_core::Edge<value_type>;
  auto expected = std::vector<edge_type>{{1, 2}, {2, 3}, {3, 1}};
  auto actual = graph.get_edges();
  EXPECT_TRUE(vectors_equal_unordered(expected, actual));
}

TYPED_TEST(GraphTest, boundary_cases) {
  TypeParam graph;

  // пустой граф
  EXPECT_EQ(graph.vertex_count(), 0);
  EXPECT_EQ(graph.edge_count(), 0);
  EXPECT_TRUE(graph.get_vertices().empty());
  EXPECT_TRUE(graph.get_edges().empty());

  // повторное добавление вершины
  graph.add_vertex(1);
  graph.add_vertex(1);
  EXPECT_EQ(graph.vertex_count(), 1);

  // повторное добавление ребра
  graph.add_edge({1, 2});
  graph.add_edge({1, 2});
  EXPECT_EQ(graph.edge_count(), 1);
}
