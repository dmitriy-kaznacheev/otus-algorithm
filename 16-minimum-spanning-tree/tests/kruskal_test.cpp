#include <mst/kruskal.h>
#include <gtest/gtest.h>

TEST(kruskal_test, connected_graph) {
  mst::Graph<int> graph(3);
  graph.add_edge(0, 1, 1);
  graph.add_edge(1, 2, 2);
  graph.add_edge(0, 2, 3);

  auto mst = mst::kruskal(graph);
  EXPECT_EQ(mst.size(), 2); // V-1 рёберо
  EXPECT_EQ(mst[0].weight, 1);
  EXPECT_EQ(mst[1].weight, 2);
}

TEST(kruskal_test, disconnected_graph) {
  mst::Graph<int> graph(4);
  graph.add_edge(0, 1, 1);
  graph.add_edge(2, 3, 2); // две отдельные компоненты

  ASSERT_THROW(mst::kruskal(graph), std::runtime_error);
}

TEST(kruskal_test, single_vertex) {
  mst::Graph<int> graph(1);
  auto mst = mst::kruskal(graph);
  EXPECT_EQ(mst.size(), 0); // для одной вершины MST пусто
}

TEST(kruskal_test, empty_graph) {
  mst::Graph<int> graph(0);
  auto mst = mst::kruskal(graph);
  EXPECT_EQ(mst.size(), 0);
}
