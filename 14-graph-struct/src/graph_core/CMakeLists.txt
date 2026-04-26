add_library(graph_core
  enumerate_graph.cpp
  adjacency_array_graph.cpp
  adjacency_list_graph.cpp
  adjacency_matrix_graph.cpp
  adjacency_vector_graph.cpp
  edge_list_graph.cpp
  incidence_matrix_graph.cpp
  indexed_graph.cpp
  vertex_edge_list_graph.cpp
)

target_include_directories(graph_core PUBLIC include)
