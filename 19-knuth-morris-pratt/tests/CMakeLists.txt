include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(kmp_test 
  kmp_test.cpp
)

target_link_libraries(kmp_test
  substr
  GTest::gtest
  GTest::gtest_main
)

add_test(NAME KMPTests COMMAND kmp_test)
