add_executable(simple_sort_test 
  simple_sort_test.cpp
)

target_link_libraries(simple_sort_test
  PRIVATE
  simple_sort
)
