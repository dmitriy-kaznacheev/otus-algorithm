add_executable(bitboard_test 
  bitboard_test.cpp
)

target_link_libraries(bitboard_test
  PRIVATE
  bitboard
)
