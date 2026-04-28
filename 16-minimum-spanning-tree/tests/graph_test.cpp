#include <mst/core.h>
#include <gtest/gtest.h>

TEST(graph_test, create) {
  mst::Graph<int> graph(3);
  EXPECT_EQ(graph.get_vertex_count(), 3);
}

TEST(graph_test, add_edges) {
  mst::Graph<int> graph(3);
  graph.add_edge(0, 1, 5);
  graph.add_edge(1, 2, 3);

  auto edges = graph.get_edges();
  EXPECT_EQ(edges.size(), 2);
  EXPECT_EQ(edges[0].from, 0);
  EXPECT_EQ(edges[0].to, 1);
  EXPECT_EQ(edges[0].weight, 5);
}

TEST(graph_test, out_of_bounds) {
  mst::Graph<int> graph(2);
  ASSERT_THROW(graph.add_edge(2, 1), std::out_of_range);
  ASSERT_THROW(graph.add_edge(1, 2), std::out_of_range);
}

TEST(graph_test, negative_weight) {
  mst::Graph<int> graph(2);
  ASSERT_THROW(graph.add_edge(0, 1, -1), std::invalid_argument);
}

TEST(graph_test, adjacency_list) {
  mst::Graph<int> graph(3);
  graph.add_edge(0, 1, 5);
  graph.add_edge(1, 2, 3);

  auto adj = graph.get_adjacency();
  EXPECT_EQ(adj[0].size(), 1);
  EXPECT_EQ(adj[1].size(), 2);
  EXPECT_EQ(adj[2].size(), 1);

  EXPECT_EQ(adj[0][0].first, 1);  // сосед вершины 0
  EXPECT_EQ(adj[0][0].second, 5); // вес ребра
}
