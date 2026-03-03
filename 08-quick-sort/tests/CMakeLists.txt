add_executable(quick_sort_test 
  quick_sort_test.cpp
)

target_link_libraries(quick_sort_test
  PRIVATE
  quick_sort
)
