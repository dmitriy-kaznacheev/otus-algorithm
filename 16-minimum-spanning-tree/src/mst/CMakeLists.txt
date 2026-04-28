add_library(mst
  core.cpp
  kruskal.cpp
  prim.cpp
  boruvka.cpp
)

target_include_directories(mst PUBLIC include)
