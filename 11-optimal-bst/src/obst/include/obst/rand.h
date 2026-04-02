#pragma once
#include <functional>
#include <memory>
#include <random>

namespace tree {
namespace rand {

template <typename T> class Rand final {
  struct Node {
    T data{};
    size_t size{1};
    std::unique_ptr<Node> left{nullptr};
    std::unique_ptr<Node> right{nullptr};

    void update() {
      size = 1 + (left ? left->size : 0) + (right ? right->size : 0);
    }
  };

public:
  void insert(T value) { root_ = insert(std::move(root_), std::move(value)); }

  void remove(const T &value) { root_ = remove(std::move(root_), value); }

  bool search(const T &value) const {
    const Node *curr = root_.get();
    while (curr) {
      if (value < curr->data) {
        curr = curr->left.get();
      } else if (curr->data < value) {
        curr = curr->right.get();
      } else {
        return true;
      }
    }
    return false;
  }

  void traverse(std::function<void(T)> visit) const {
    inorder_traverse(root_.get(), visit);
  }

  bool is_valid_bst() const {
    return is_valid_bst_helper(root_.get(), nullptr, nullptr);
  }

  ~Rand() = default;

private:
  bool is_valid_bst_helper(const Node *node, const T *min_val,
                           const T *max_val) const {
    if (!node) {
      return true;
    }

    if ((min_val && node->data <= *min_val) ||
        (max_val && node->data >= *max_val)) {
      return false;
    }

    return is_valid_bst_helper(node->left.get(), min_val, &node->data) &&
           is_valid_bst_helper(node->right.get(), &node->data, max_val);
  }

  std::unique_ptr<Node> rotate_right(std::unique_ptr<Node> node) {
    if (!node || !node->left) {
      return node;
    }

    auto new_node = std::move(node->left);
    node->left = std::move(new_node->right);
    node->update();
    new_node->right = std::move(node);
    new_node->update();

    return new_node;
  }

  std::unique_ptr<Node> rotate_left(std::unique_ptr<Node> node) {
    if (!node || !node->right) {
      return node;
    }

    auto new_node = std::move(node->right);
    node->right = std::move(new_node->left);
    node->update();
    new_node->left = std::move(node);
    new_node->update();

    return new_node;
  }

  std::unique_ptr<Node> insert_root(std::unique_ptr<Node> node, T value) {
    if (!node) {
      return std::make_unique<Node>(std::move(value));
    }

    if (value < node->data) {
      node->left = insert_root(std::move(node->left), std::move(value));
      return rotate_right(std::move(node));
    } else if (node->data < value) {
      node->right = insert_root(std::move(node->right), std::move(value));
      return rotate_left(std::move(node));
    } else {
      return node;
    }
  }

  std::unique_ptr<Node> insert(std::unique_ptr<Node> node, T value) {
    if (!node) {
      return std::make_unique<Node>(std::move(value));
    }

    // вероятность вставки в корень: 1 / (size + 1)
    std::uniform_int_distribution<size_t> dist(1, node->size + 1);
    if (dist(gen()) == 1) {
      return insert_root(std::move(node), std::move(value));
    }

    if (value < node->data) {
      node->left = insert(std::move(node->left), std::move(value));
    } else if (node->data < value) {
      node->right = insert(std::move(node->right), std::move(value));
    }

    node->update();
    return node;
  }

  std::unique_ptr<Node> merge(std::unique_ptr<Node> lhs,
                              std::unique_ptr<Node> rhs) {
    if (!lhs) {
      return rhs;
    }
    if (!rhs) {
      return lhs;
    }

    std::uniform_int_distribution<size_t> dist(0, lhs->size + rhs->size - 1);
    if (dist(gen()) < lhs->size) {
      lhs->right = merge(std::move(lhs->right), std::move(rhs));
      lhs->update();
      return lhs;
    } else {
      rhs->left = merge(std::move(lhs), std::move(rhs->left));
      rhs->update();
      return rhs;
    }
  }

  std::unique_ptr<Node> remove(std::unique_ptr<Node> node, const T &value) {
    if (!node) {
      return nullptr;
    }

    if (node->data == value) {
      auto left = std::move(node->left);
      auto right = std::move(node->right);
      return merge(std::move(left), std::move(right));
    }

    if (value < node->data) {
      node->left = remove(std::move(node->left), value);
    } else if (node->data < value) {
      node->right = remove(std::move(node->right), value);
    }

    node->update();
    return node;
  }

  void inorder_traverse(const Node *node, std::function<void(T)> visit) const {
    if (!node) {
      return;
    }

    inorder_traverse(node->left.get(), visit);
    visit(node->data);
    inorder_traverse(node->right.get(), visit);
  }

  static std::mt19937 &gen() {
    static std::mt19937 gen{std::random_device{}()};
    return gen;
  }

private:
  std::unique_ptr<Node> root_{nullptr};
};

} // namespace rand
} // namespace tree
