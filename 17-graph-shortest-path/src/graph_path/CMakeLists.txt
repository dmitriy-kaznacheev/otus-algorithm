add_library(graph_path
  graph_core.cpp
  dejkstra.cpp
  belman_ford.cpp
)

target_include_directories(graph_path PUBLIC include)
