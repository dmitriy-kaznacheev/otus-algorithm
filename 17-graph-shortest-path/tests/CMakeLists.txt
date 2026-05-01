include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(graph_path_test 
  graph_path_test.cpp
)

target_link_libraries(graph_path_test
  graph_path
  GTest::gtest
  GTest::gtest_main
)

add_test(NAME GraphShortestPathTests COMMAND graph_path_test)
