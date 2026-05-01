#include <gtest/gtest.h>
#include <mst/kruskal.h>

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

TEST(kruskal_test, disconnected_graph_msf) {
  mst::Graph<int> graph(4);
  graph.add_edge(0, 1, 1);
  graph.add_edge(2, 3, 2); // две отдельные компоненты

  auto msf = mst::kruskal(graph, false);
  EXPECT_EQ(msf.size(), 2);

  std::vector<int> weights;
  for (const auto &e : msf) {
    weights.push_back(e.weight);
  }
  std::sort(weights.begin(), weights.end());
  EXPECT_EQ(weights[0], 1);
  EXPECT_EQ(weights[1], 2);

  // структурf рёбер (неупорядоченные пары)
  std::set<std::pair<int, int>> edges_set;
  for (const auto &e : msf) {
    edges_set.insert({std::min(e.from, e.to), std::max(e.from, e.to)});
  }
  EXPECT_TRUE(edges_set.count({0, 1}));
  EXPECT_TRUE(edges_set.count({2, 3}));
}

TEST(kruskal_test, three_components_msf) {
  mst::Graph<int> graph(6);
  // Компонента 1: вершины 0,1
  graph.add_edge(0, 1, 10);
  // Компонента 2: вершины 2,3,4
  graph.add_edge(2, 3, 5);
  graph.add_edge(3, 4, 8);
  graph.add_edge(2, 4, 12);
  // Компонента 3: вершина 5 (изолированная)

  auto msf = mst::kruskal(graph, false);
  EXPECT_EQ(msf.size(), 3);

  std::vector<int> weights;
  for (const auto &e : msf) {
    weights.push_back(e.weight);
  }
  std::sort(weights.begin(), weights.end());
  EXPECT_EQ(weights[0], 5);  // ребро 2-3
  EXPECT_EQ(weights[1], 8);  // ребро 3-4
  EXPECT_EQ(weights[2], 10); // ребро 0-1
}

TEST(kruskal_test, isolated_vertices_msf) {
  mst::Graph<int> graph(5);
  // изолированные вершины, нет рёбер

  auto msf = mst::kruskal(graph, false);
  EXPECT_EQ(msf.size(), 0);
}

TEST(kruskal_test, graph_with_parallel_edges_msf) {
  mst::Graph<int> graph(4);
  // две компоненты, в каждой параллельные рёбра
  graph.add_edge(0, 1, 15);
  graph.add_edge(0, 1, 7); // это должно попасть в MSF
  graph.add_edge(2, 3, 20);
  graph.add_edge(2, 3, 12); // это должно попасть в MSF

  auto msf = mst::kruskal(graph, false);
  EXPECT_EQ(msf.size(), 2);

  std::vector<int> weights;
  for (const auto &e : msf) {
    weights.push_back(e.weight);
  }
  std::sort(weights.begin(), weights.end());
  EXPECT_EQ(weights[0], 7);
  EXPECT_EQ(weights[1], 12);
}

TEST(kruskal_test, single_vertex_msf) {
  mst::Graph<int> graph(1);
  auto msf = mst::kruskal(graph, false);
  EXPECT_EQ(msf.size(), 0); // для одной вершины MSF пусто
}

TEST(kruskal_test, empty_graph_msf) {
  mst::Graph<int> graph(0);
  auto msf = mst::kruskal(graph, false);
  EXPECT_EQ(msf.size(), 0);
}

TEST(kruskal_test, complex_disconnected_msf) {
  mst::Graph<int> graph(7);
  // компонента 1: треугольник с весами 1,2,3
  graph.add_edge(0, 1, 1);
  graph.add_edge(1, 2, 2);
  graph.add_edge(0, 2, 3);
  // компонента 2: линия с весами 4,5
  graph.add_edge(3, 4, 4);
  graph.add_edge(4, 5, 5);
  // компонента 3: изолированная вершина 6

  auto msf = mst::kruskal(graph, false);
  EXPECT_EQ(msf.size(), 4);

  std::vector<int> weights;
  for (const auto &e : msf) {
    weights.push_back(e.weight);
  }
  std::sort(weights.begin(), weights.end());
  EXPECT_EQ(weights[0], 1); // компонент 1
  EXPECT_EQ(weights[1], 2); // компонент 1
  EXPECT_EQ(weights[2], 4); // компонент 2
  EXPECT_EQ(weights[3], 5); // компонент 2
}

TEST(kruskal_test, same_weights_msf) {
  mst::Graph<int> graph(4);
  // все рёбра с одним весом
  graph.add_edge(0, 1, 5);
  graph.add_edge(2, 3, 5);

  auto msf = mst::kruskal(graph, false);
  EXPECT_EQ(msf.size(), 2);

  for (const auto &e : msf) {
    EXPECT_EQ(e.weight, 5);
  }
}