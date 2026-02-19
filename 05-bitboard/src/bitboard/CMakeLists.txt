add_library(bitboard
  king.cpp
  knight.cpp
  rook.cpp
  bishop.cpp
  queen.cpp
)

target_include_directories(bitboard PUBLIC include)
