add_executable(obst_test 
  obst_test.cpp
)

target_link_libraries(obst_test
  PRIVATE
  obst
)
