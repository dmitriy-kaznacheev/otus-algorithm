include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(graph_test 
  graph_test.cpp
)

target_link_libraries(graph_test
  graph_core
  GTest::gtest
  GTest::gtest_main
)

add_test(NAME GraphTests COMMAND graph_test)
