include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(archiver_test 
  algorithm_rle_test.cpp
  archiver_test.cpp
)

target_link_libraries(archiver_test
  archiver
  GTest::gtest
  GTest::gtest_main
)

add_test(NAME ArchiverTests COMMAND archiver_test)
