#include "utils.h"

#include <bst/avl.h>
#include <bst/bst.h>
#include <bst/treap.h>

using value_type = long;

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

  using namespace tree::bst;
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

  using namespace tree::avl;
  AVL<value_type> avl;
  auto size = std::distance(first, last);

  {
    std::set<value_type> expected(first, last);
    auto duration = insert(avl, first, last);
    bool result = check(avl, expected.begin(), expected.end());
    show_result(result, duration, size, "insert"sv);
  }

  {
    bool is_avl = avl.is_avl();
    std::cout << (is_avl ? "[ + ] "sv : "[ - ] "sv) << "is balanced before\n"sv;
  }

  {
    auto rnd_items = choose_random_items(first, last, size / 10);
    auto [result, duration] = search(avl, rnd_items.begin(), rnd_items.end());
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
    auto duration = remove(avl, rnd_items.begin(), rnd_items.end());
    bool result = check(avl, expected.begin(), expected.end());
    show_result(result, duration, rnd_items.size(), "remove"sv);
  }

  {
    bool is_avl = avl.is_avl();
    std::cout << (is_avl ? "[ + ] "sv : "[ - ] "sv) << "is balanced after\n"sv;
  }

  std::cout << std::endl;
}

template <typename It>
void treap_test(It first, It last, std::string_view seq_type) {
  std::cout << "--- treap binary search tree ["sv << seq_type << "] ---\n"sv;

  using namespace tree::treap;
  Treap<value_type> treap;
  auto size = std::distance(first, last);

  {
    std::set<value_type> expected(first, last);
    auto duration = insert(treap, first, last);
    bool result = check(treap, expected.begin(), expected.end());
    show_result(result, duration, size, "insert"sv);
  }

  {
    bool is_treap = treap.is_treap();
    std::cout << (is_treap ? "[ + ] "sv : "[ - ] "sv)
              << "is balanced before\n"sv;
  }

  {
    auto rnd_items = choose_random_items(first, last, size / 10);
    auto [result, duration] = search(treap, rnd_items.begin(), rnd_items.end());
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
    auto duration = remove(treap, rnd_items.begin(), rnd_items.end());
    bool result = check(treap, expected.begin(), expected.end());
    show_result(result, duration, rnd_items.size(), "remove"sv);
  }

  {
    bool is_treap = treap.is_treap();
    std::cout << (is_treap ? "[ + ] "sv : "[ - ] "sv)
              << "is balanced after\n"sv;
  }

  std::cout << std::endl;
}

int main() {
  const auto inc_seq_small = gen_increasing<value_type>(25'000);
  const auto inc_seq_big = gen_increasing<value_type>(10'000'000);
  const auto rnd_seq_big = gen_random<value_type>(10'000'000);

  bst_test(std::begin(inc_seq_small), std::end(inc_seq_small), "increasing"sv);
  bst_test(std::begin(rnd_seq_big), std::end(rnd_seq_big), "random"sv);

  avl_test(std::begin(inc_seq_big), std::end(inc_seq_big), "increasing"sv);
  avl_test(std::begin(rnd_seq_big), std::end(rnd_seq_big), "random"sv);

  treap_test(std::begin(inc_seq_big), std::end(inc_seq_big), "increasing"sv);
  treap_test(std::begin(rnd_seq_big), std::end(rnd_seq_big), "random"sv);

  return 0;
}