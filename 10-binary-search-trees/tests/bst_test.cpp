#include "utils.h"

#include <bst/avl.h>
#include <bst/bst.h>
#include <bst/treap.h>

using namespace tree::bst;
using value_type = int;

template <typename Tree, typename It>
size_t insert(Tree &tree, It first, It last) {
  size_t duration{};
  {
    Timer t;
    for (auto it = first; it != last; ++it) {
      tree.insert(*it);
    }
    duration = t.duration();
  }
  return duration;
}

template <typename Tree, typename It>
std::pair<bool, size_t> search(const Tree &tree, It first, It last) {
  bool result{true};
  size_t duration{};
  {
    Timer t;
    for (auto it = first; it != last; ++it) {
      bool ok = tree.search(*it);
      result = result && ok;
    }
    duration = t.duration();
  }
  return {result, duration};
}

template <typename Tree, typename It>
size_t remove(Tree &tree, It first, It last) {
  size_t duration{};
  {
    Timer t;
    for (auto it = first; it != last; ++it) {
      tree.remove(*it);
    }
    duration = t.duration();
  }
  return duration;
}

template <typename It>
void bst_test(It first, It last, std::string_view seq_type) {
  std::cout << "--- binary search tree ["sv << seq_type << "] ---\n"sv;

  BST<value_type> bst;
  auto size = std::distance(first, last);

  {
    std::set<value_type> expected(first, last);
    auto duration = insert(bst, first, last);
    bool result = check(bst, expected.begin(), expected.end());
    show_result(result, duration, size, "insert"sv);
  }

  {
    auto rnd_items = choose_random_items(first, last, size / 10);
    auto [result, duration] = search(bst, rnd_items.begin(), rnd_items.end());
    show_result(result, duration, rnd_items.size(), "search"sv);
  }

  {
    auto rnd_items = choose_random_items(first, last, size / 10);
    std::set<value_type> expected(first, last);
    {
      for (auto value : rnd_items) {
        expected.erase(value);
      }
    }
    auto duration = remove(bst, rnd_items.begin(), rnd_items.end());
    bool result = check(bst, expected.begin(), expected.end());
    show_result(result, duration, rnd_items.size(), "remove"sv);
  }

  std::cout << std::endl;
}

template <typename It>
void avl_test(It first, It last, std::string_view seq_type) {
  std::cout << "--- avl binary search tree ["sv << seq_type << "] ---\n"sv;

  std::cout << std::endl;
}

template <typename It>
void treap_test(It first, It last, std::string_view seq_type) {
  std::cout << "--- treap binary search tree ["sv << seq_type << "] ---\n"sv;

  std::cout << std::endl;
}

int main() {
  const auto inc_squence = gen_increasing<value_type>(25'000);
  const auto rnd_squence = gen_random<value_type>(10'000'000);

  bst_test(std::begin(inc_squence), std::end(inc_squence), "increasing"sv);
  bst_test(std::begin(rnd_squence), std::end(rnd_squence), "random"sv);

#if 0
  avl_test(std::begin(inc_squence), std::end(inc_squence), "increasing"sv);
  avl_test(std::begin(rnd_squence), std::end(rnd_squence), "random"sv);

  treap_test(std::begin(inc_squence), std::end(inc_squence), "increasing"sv);
  treap_test(std::begin(rnd_squence), std::end(rnd_squence), "random"sv);
#endif

  return 0;
}