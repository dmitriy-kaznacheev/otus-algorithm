add_executable(bitboard_test 
  bitboard_test.cpp
  king_test.cpp
  knight_test.cpp
  rook_test.cpp
  bishop_test.cpp
  queen_test.cpp
)

target_link_libraries(bitboard_test
  PRIVATE
  bitboard
)
