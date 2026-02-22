add_library(simple_sort
  bubble_sort.cpp
  insertion_sort.cpp
  shell_sort.cpp
)

target_include_directories(simple_sort PUBLIC include)
