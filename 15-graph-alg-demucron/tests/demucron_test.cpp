#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

#include <demucron/adjacency_matrix.h>
#include <demucron/demucron.h>

using namespace graph_utils;

TEST(demucron_test, dag) {
  AdjacencyMatrix<int> graph{6};
  graph.add_edge(0, 1);
  graph.add_edge(0, 2);
  graph.add_edge(1, 3);
  graph.add_edge(2, 3);
  graph.add_edge(3, 4);
  graph.add_edge(3, 5);

  auto actual = demucron_sort(graph);
  auto expected_l0 = std::vector<size_t>{0};
  auto expected_l1 = std::vector<size_t>{1, 2};
  auto expected_l2 = std::vector<size_t>{3};
  auto expected_l3 = std::vector<size_t>{4, 5};

  EXPECT_EQ(actual.size(), 4);
  EXPECT_EQ(expected_l0, actual[0]);
  EXPECT_EQ(expected_l1, actual[1]);
  EXPECT_EQ(expected_l2, actual[2]);
  EXPECT_EQ(expected_l3, actual[3]);
}

TEST(demucron_test, cyclic) {
  AdjacencyMatrix<int> graph{3};
  graph.add_edge(0, 1);
  graph.add_edge(1, 2);
  graph.add_edge(2, 0); // цикл

  EXPECT_THROW(demucron_sort(graph), std::runtime_error);
}

TEST(demucron_test, disconnected) {
  AdjacencyMatrix<int> graph{3};
  // нет ребер -- изолирвоанные вершины

  auto actual = demucron_sort(graph);

  // все вершины на "0" уровне
  EXPECT_EQ(actual.size(), 1);
  EXPECT_EQ(actual[0].size(), 3);
}
