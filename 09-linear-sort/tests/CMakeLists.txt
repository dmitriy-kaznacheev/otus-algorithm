add_executable(linear_sort_test 
  linear_sort_test.cpp
)

target_link_libraries(linear_sort_test
  PRIVATE
  linear_sort
)
