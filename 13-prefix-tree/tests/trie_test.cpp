#include "utils.h"

#include <trie/trie_map.h>

int main() {
  using namespace trie;

  const size_t size{1'000'000};
  const auto data = generate_random_strings(size, 10, 20);

  TrieMap<char, long> map;

  {
    Timer t;
    long value{};
    for (auto it = data.begin(); it != data.end(); ++it) {
      map.insert(*it, std::move(value));
      ++value;
    }
    show_result(true, t.duration(), size, "insert"sv);
  }

  {
    Timer t;
    bool result{true};
    long value{};
    for (auto it = data.begin(); it != data.end(); ++it) {
      long *val = map.get(*it);
      if ((val == nullptr) || (*val != value)) {
        std::cout << (*val) << " " << value << std::endl;
        result = false;
        break;
      }
      ++value;
    }
    show_result(result, t.duration(), size, "search"sv);
  }

  {
    Timer t;
    for (auto it = data.begin(); it != data.end(); ++it) {
      map.remove(*it);
    }
    show_result(true, t.duration(), size, "remove"sv);
  }

  {
    Timer t;
    bool result{true};
    long value{};
    for (auto it = data.begin(); it != data.end(); ++it) {
      auto *val = map.get(*it);
      if (val && (*val == value)) {
        result = false;
        break;
      }
      ++value;
    }
    show_result(result, t.duration(), size, "search"sv);
  }

  return 0;
}
