include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(mst_test 
  graph_test.cpp
  dsu_test.cpp
  kruskal_test.cpp
  prim_test.cpp
)

target_link_libraries(mst_test
  mst
  GTest::gtest
  GTest::gtest_main
)

add_test(NAME MSTTests COMMAND mst_test)

