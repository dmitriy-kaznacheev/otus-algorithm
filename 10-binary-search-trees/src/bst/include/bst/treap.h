#pragma once
#include <functional>
#include <memory>
#include <random>

namespace tree {
namespace treap {

namespace detail {
using priority_type = long;
constexpr priority_type min_priority =
    std::numeric_limits<priority_type>::min();
constexpr priority_type max_priority =
    std::numeric_limits<priority_type>::max();
static std::random_device rd;
static std::mt19937 mt{rd()};
static std::uniform_int_distribution<priority_type> dist(min_priority,
                                                         max_priority);
} // namespace detail

template <typename T, typename Compare = std::less<T>> class Treap final {
  struct Node {
    T data;
    detail::priority_type priority{detail::dist(detail::mt)};
    std::unique_ptr<Node> left{nullptr};
    std::unique_ptr<Node> right{nullptr};
  };

  struct SplitTreap {
    std::unique_ptr<Node> left{nullptr};
    std::unique_ptr<Node> right{nullptr};
  };

public:
  void insert(T value) { root_ = insert(std::move(root_), value); }
  void remove(T value) { root_ = remove(std::move(root_), value); }
  bool search(T value) const { return (search(root_.get(), value) != nullptr); }
  void traverse(std::function<void(T)> visit) const {
    inorder_traverse(root_.get(), visit);
  };
  bool is_treap() const {
    T min_value = std::numeric_limits<T>::min();
    T max_value = std::numeric_limits<T>::max();
    return is_valid(root_.get(), min_value, max_value, detail::max_priority);
  }

  ~Treap() = default;

private:
  SplitTreap split(std::unique_ptr<Node> node, T value) {
    if (!node) {
      return {};
    }

    if (is_less(node->data, value)) {
      auto treap = split(std::move(node->right), value);
      node->right = std::move(treap.left);
      return {std::move(node), std::move(treap.right)};
    } else {
      auto treap = split(std::move(node->left), value);
      node->left = std::move(treap.right);
      return {std::move(treap.left), std::move(node)};
    }
  }

  std::unique_ptr<Node> merge(std::unique_ptr<Node> l,
                              std::unique_ptr<Node> r) {
    if (!l || !r) {
      return std::move(l ? l : r);
    }

    if (l->priority > r->priority) {
      l->right = merge(std::move(l->right), std::move(r));
      return l;
    } else {
      r->left = merge(std::move(l), std::move(r->left));
      return r;
    }
  }

  bool is_valid(Node *node, T min_value, T max_value,
                detail::priority_type max_priority) const {
    if (!node) {
      return true;
    }

    if (is_less(node->data, min_value) || is_less(max_value, node->data)) {
      return false;
    }

    if ((node->priority > max_priority)) {
      return false;
    }

    return is_valid(node->left.get(), min_value, node->data, node->priority) &&
           is_valid(node->right.get(), node->data, max_value, node->priority);
  }

private:
  std::unique_ptr<Node> insert(std::unique_ptr<Node> node, T value) {
    if (search(node.get(), value)) {
      return nullptr;
    }
    auto treap = split(std::move(node), value);
    auto new_node = std::make_unique<Node>(value);
    return merge(merge(std::move(treap.left), std::move(new_node)),
                 std::move(treap.right));
  }

  std::unique_ptr<Node> remove(std::unique_ptr<Node> node, T value) {
    if (!node) {
      return nullptr;
    }

    if (is_equal(value, node->data)) {
      return merge(std::move(node->left), std::move(node->right));
    }
    if (is_less(value, node->data)) {
      node->left = remove(std::move(node->left), value);
    } else {
      node->right = remove(std::move(node->right), value);
    }
    return node;
  }

  Node *search(Node *node, T value) const {
    if (!node) {
      return nullptr;
    }

    if (is_equal(value, node->data)) {
      return node;
    } else if (is_less(value, node->data)) {
      return search(node->left.get(), value);
    } else {
      return search(node->right.get(), value);
    }
  }

  void inorder_traverse(const Node *node, std::function<void(T)> visit) const {
    if (!node) {
      return;
    }
    inorder_traverse(node->left.get(), visit);
    visit(node->data);
    inorder_traverse(node->right.get(), visit);
  }

  Node *find_min(Node *node) {
    while (node && node->left) {
      node = node->left.get();
    }
    return node;
  }

  bool is_equal(const T &lhs, const T &rhs) const {
    return !is_less(lhs, rhs) && !is_less(rhs, lhs);
  }

private:
  std::unique_ptr<Node> root_{nullptr};
  Compare is_less;
};

} // namespace treap
} // namespace tree