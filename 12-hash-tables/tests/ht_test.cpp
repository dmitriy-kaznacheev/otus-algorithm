#include "utils.h"

#include <ht/chain.h>
#include <ht/opena.h>

template <typename HT, typename It>
std::pair<bool, size_t> insert(HT &ht, It first, It last) {
  bool result{true};
  size_t duration{};
  size_t index{};
  {
    Timer t;
    for (auto it = first; it != last; ++it) {
      result = ht.insert(index++, *it);
      if (!result) {
        break;
      }
    }
    duration = t.duration();
  }
  return {result, duration};
}

template <typename HT, typename It>
std::pair<bool, size_t> get(HT &ht, It first, It last) {
  bool result{true};
  size_t duration{};
  size_t index{};
  {
    Timer t;
    for (auto it = first; it != last; ++it) {
      auto value = ht.get(index++);
      if (!value || *value != *it) {
        result = false;
        break;
      }
    }
    duration = t.duration();
  }
  return {result, duration};
}

template <typename HT, typename It>
std::pair<bool, size_t> remove(HT &ht, It first, It last) {
  bool result{true};
  size_t duration{};
  size_t index{};
  {
    Timer t;
    for (auto it = first; it != last; ++it) {
      result = ht.remove(index++);
      if (!result) {
        break;
      }
    }
    duration = t.duration();
  }
  return {result, duration};
}

template <typename HT> void test(std::string_view test_name) {
  std::cout << "--- hash table ["sv << test_name << "] ---\n"sv;

  size_t size{1'000'000};
  std::vector<int> v(size);
  std::iota(v.begin(), v.end(), 1);

  HT ht{size / 1000};

  {
    auto [result, duration] = insert(ht, v.begin(), v.end());
    show_result(result, duration, size, "insert"sv);
  }

  {
    auto [result, duration] = get(ht, v.begin(), v.end());
    show_result(result, duration, size, "get before"sv);
  }

  {
    Timer t;
    ht.rehash();
    show_result(true, t.duration(), size, "rehash"sv);
  }

  {
    auto [result, duration] = get(ht, v.begin(), v.end());
    show_result(result, duration, size, "get after"sv);
  }

  {
    auto [result, duration] = remove(ht, v.begin(), v.end());
    show_result(result, duration, size, "remove"sv);
  }

  std::cout << std::endl;
}

int main() {
  using namespace hash;

  test<chain::Table<size_t, int>>("chain"sv);
  test<opena::Table<size_t, int>>("opena"sv);

  return 0;
}
