add_executable(trie_test 
  trie_test.cpp
)

target_link_libraries(trie_test
  PRIVATE
  trie
)
