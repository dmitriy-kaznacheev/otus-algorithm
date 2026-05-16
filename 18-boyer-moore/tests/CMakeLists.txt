include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(substr_test 
  substr_test.cpp
)

target_link_libraries(substr_test
  substr
  GTest::gtest
  GTest::gtest_main
)

add_test(NAME BoyerMooreTests COMMAND substr_test)
