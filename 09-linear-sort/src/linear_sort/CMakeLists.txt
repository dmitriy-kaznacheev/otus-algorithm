add_library(linear_sort
  bucket_sort.cpp
  counting_sort.cpp
  radix_sort.cpp
)

target_include_directories(linear_sort PUBLIC include)
