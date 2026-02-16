add_library(priority_queue priority_queue.cpp)

target_include_directories(priority_queue PUBLIC include)

target_link_libraries(priority_queue
  PRIVATE
  dynamic_array
)
