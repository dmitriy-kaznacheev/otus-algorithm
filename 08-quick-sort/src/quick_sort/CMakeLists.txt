add_library(quick_sort
  quick_sort.cpp 
  merge_sort.cpp 
  external_sort.cpp
)

target_include_directories(quick_sort PUBLIC include)
