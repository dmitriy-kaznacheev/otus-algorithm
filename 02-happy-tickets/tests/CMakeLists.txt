add_executable(solver_test solver_test.cpp)

target_link_libraries(solver_test
  PRIVATE
  solver
)

