#include "utils.h"

#include <obst/rand.h>
#include <obst/splay.h>

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
std::pair<bool, size_t> search(Tree &tree, It first, It last) {
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

template <typename Tree, typename It>
void test(It first, It last, std::string_view test_name) {
  std::cout << "--- "sv << test_name << " ---\n"sv;

  auto size = std::distance(first, last);
  Tree tree;

  {
    std::set<value_type> expected(first, last);
    auto duration = insert(tree, first, last);
    bool result = check(tree, expected.begin(), expected.end());
    show_result(result, duration, size, "insert"sv);
  }

  {
    bool is_bst = tree.is_valid_bst();
    std::cout << (is_bst ? "[ + ] "sv : "[ - ] "sv)
              << "is valid bst before\n"sv;
  }

  {
    auto rnd_items = choose_random_items(first, last, size / 10);
    auto [result, duration] = search(tree, rnd_items.begin(), rnd_items.end());
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
    auto duration = remove(tree, rnd_items.begin(), rnd_items.end());
    bool result = check(tree, expected.begin(), expected.end());
    show_result(result, duration, rnd_items.size(), "remove"sv);
  }

  {
    bool is_bst = tree.is_valid_bst();
    std::cout << (is_bst ? "[ + ] "sv : "[ - ] "sv) << "is valid bst after\n"sv;
  }

  std::cout << std::endl;
}

int main() {
  const size_t size{1'000'000};
  const auto data = gen_random<value_type>(size);

  {
    using tree_type = typename tree::splay::Splay<value_type>;
    test<tree_type>(std::begin(data), std::end(data),
                    "Splay Binary Search Tree"sv);
  }

  {
    using tree_type = typename tree::rand::Rand<value_type>;
    test<tree_type>(std::begin(data), std::end(data),
                    "Randomize Binary Search Tree"sv);
  }

  return 0;
}