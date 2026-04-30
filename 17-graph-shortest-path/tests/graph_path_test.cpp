#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

#include <graph_path/belman_ford.h>
#include <graph_path/dejkstra.h>
#include <graph_path/graph_core.h>

using namespace graph_path;

TEST(dejkstra_test, normal_path) {
  auto graph = Graph<int>(5);
  graph.add_edge(0, 1, 9);
  graph.add_edge(0, 4, 3);
  graph.add_edge(4, 1, 1);
  graph.add_edge(1, 2, 2);
  graph.add_edge(4, 2, 8);
  graph.add_edge(2, 3, 7);
  graph.add_edge(4, 3, 2);

  auto dist = dejkstra(graph, 0);
  EXPECT_EQ(dist[1], 4); // 0-4-1
  EXPECT_EQ(dist[3], 5); // 0-4-3
}

TEST(dejkstra_test, unreachable_path) {
  auto graph = Graph<int>(3);
  graph.add_edge(0, 1, 3);
  // вершины 2 изолирована

  auto dist = dejkstra(graph, 0);
  auto inf = std::numeric_limits<int>::max();
  EXPECT_EQ(dist[2], inf);
}

TEST(belman_ford_test, negative_weights) {
  auto graph = Graph<int>(4);
  graph.add_edge(0, 1, 5);
  graph.add_edge(1, 2, -2);
  graph.add_edge(2, 3, -3);
  graph.add_edge(0, 3, 9);

  auto dist = belman_ford(graph, 0);

  EXPECT_TRUE(dist.has_value());
  EXPECT_EQ((*dist)[3], 0); // 0-1-2-3
  EXPECT_EQ((*dist)[2], 3); // 0-1-2
}

TEST(belman_ford_test, negative_cycle) {
  auto graph = Graph<int>(3);
  graph.add_edge(0, 1, 1);
  graph.add_edge(1, 2, 1);
  graph.add_edge(2, 0, -5); // отрицательный цикл

  auto dist = belman_ford(graph, 0);
  EXPECT_FALSE(dist.has_value());
}

TEST(belman_ford_test, unreachable_path) {
  auto graph = Graph<int>(3);
  graph.add_edge(0, 1, 3);
  // вершины 2 изолирована

  auto dist = belman_ford(graph, 0);
  auto inf = std::numeric_limits<int>::max();
  EXPECT_TRUE(dist.has_value());
  EXPECT_EQ((*dist)[2], inf);
}

TEST(template_test, double_weights) {
  auto graph = Graph<double>(2);

  double weight = 3.7;
  graph.add_edge(0, 1, weight);

  {
    auto dist = dejkstra(graph, 0);
    EXPECT_DOUBLE_EQ(dist[1], weight);
  }

  {
    auto dist = belman_ford(graph, 0);
    EXPECT_DOUBLE_EQ((*dist)[1], weight);
  }
}
