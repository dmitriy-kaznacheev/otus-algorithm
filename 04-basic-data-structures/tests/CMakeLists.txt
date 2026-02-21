add_executable(basic_ds_test 
  basic_ds_test.cpp
  dynamic_array_test.cpp
  priority_queue_test.cpp
  sparse_array_test.cpp
)

target_link_libraries(basic_ds_test
  PRIVATE
  dynamic_array
  priority_queue
  sparse_array
)

