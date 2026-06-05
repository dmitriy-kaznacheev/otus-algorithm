include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(dp_test 
  peas_division_test.cpp
  christmas_tree_test.cpp
  five_and_eight_test.cpp
  big_island_test.cpp
)

target_link_libraries(dp_test
  dp
  GTest::gtest
  GTest::gtest_main
)

target_compile_definitions(dp_test 
  PRIVATE 
  DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data"
)

add_test(NAME DynamicProgrammingTests COMMAND dp_test)
