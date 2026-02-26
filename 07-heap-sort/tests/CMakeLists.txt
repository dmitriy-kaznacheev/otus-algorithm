add_executable(heap_sort_test 
  heap_sort_test.cpp
)

target_link_libraries(heap_sort_test
  PRIVATE
  heap_sort
)
