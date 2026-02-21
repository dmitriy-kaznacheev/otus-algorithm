add_library(sparse_array sparse_array.cpp)

target_include_directories(sparse_array PUBLIC include)

target_link_libraries(sparse_array
  PRIVATE
  dynamic_array
)
