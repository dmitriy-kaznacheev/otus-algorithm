#include "utils.h"

#include <trie/trie_map.h>

int main() {
  using namespace trie;

  TrieMap<char, std::string> map;

  auto data{"test string"s};
  map.insert("key1"sv, std::move(data));
  std::cout << "containts 'key1': "sv << (map.get("key1"sv) != nullptr) << std::endl;

  map.remove("key1"sv);
  std::cout << "after remove:     "sv << (map.get("key1"sv) != nullptr) << std::endl;

  return 0;
}
