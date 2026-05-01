include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(demucron_test 
  demucron_test.cpp
)

target_link_libraries(demucron_test
  demucron
  GTest::gtest
  GTest::gtest_main
)

add_test(NAME DemucronTests COMMAND demucron_test)
