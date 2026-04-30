#include <gtest/gtest.h>
#include <mst/prim.h>

TEST(prim_test, connected_graph) {
  mst::Graph<int> graph(3);
  graph.add_edge(0, 1, 1);
  graph.add_edge(1, 2, 2);
  graph.add_edge(0, 2, 3);

  auto mst = mst::prim(graph, 0);
  EXPECT_EQ(mst.size(), 2);

  int total_weight = 0;
  for (const auto &edge : mst) {
    total_weight += edge.weight;
  }
  EXPECT_EQ(total_weight, 3); // 1 + 2
}

TEST(prim_test, disconnected_graph) {
  mst::Graph<int> graph(4);
  graph.add_edge(0, 1, 1);
  graph.add_edge(2, 3, 2);

  ASSERT_THROW(mst::prim(graph, 0), std::runtime_error);
}

TEST(prim_test, different_start_vertex) {
  mst::Graph<int> graph(3);
  graph.add_edge(0, 1, 1);
  graph.add_edge(1, 2, 2);
  graph.add_edge(0, 2, 4);

  auto mst1 = mst::prim(graph, 0);
  auto mst2 = mst::prim(graph, 2);

  EXPECT_EQ(mst1.size(), 2);
  EXPECT_EQ(mst2.size(), 2);

  // вес MST не должен зависеть от стартовой вершины
  int weight1 = std::accumulate(
      mst1.begin(), mst1.end(), 0,
      [](int sum, const auto &edge) { return sum + edge.weight; });
  int weight2 = std::accumulate(
      mst2.begin(), mst2.end(), 0,
      [](int sum, const auto &edge) { return sum + edge.weight; });

  EXPECT_EQ(weight1, weight2);
}

TEST(prim_test, invalid_start_vertex) {
  mst::Graph<int> graph(2);
  auto mst = mst::prim(graph, 5); // некорректная стартовая вершина
  EXPECT_EQ(mst.size(), 0);
}
