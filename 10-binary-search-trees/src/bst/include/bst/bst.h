#pragma once
#include <functional>
#include <memory>

namespace tree {
namespace bst {

template <typename T> class BST final {
  struct Node {
    T data;
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

  ~BST() = default;

private:
  std::unique_ptr<Node> insert(std::unique_ptr<Node> node, T value) {
    if (!node) {
      return std::make_unique<Node>(value);
    }

    if (value < node->data) {
      node->left = insert(std::move(node->left), value);
    } else if (value > node->data) {
      node->right = insert(std::move(node->right), value);
    }
    return node;
  }

  std::unique_ptr<Node> remove(std::unique_ptr<Node> node, T value) {
    if (!node) {
      return nullptr;
    }

    if (value < node->data) {
      node->left = remove(std::move(node->left), value);
    } else if (value > node->data) {
      node->right = remove(std::move(node->right), value);
    } else {
      if (node->left == nullptr) {
        return std::move(node->right);
      } else if (node->right == nullptr) {
        return std::move(node->left);
      } else {
        Node *temp = find_min(node->right.get());
        node->data = temp->data;
        node->right = remove(std::move(node->right), temp->data);
      }
    }
    return node;
  }

  Node *search(Node *node, T value) const {
    if (!node) {
      return nullptr;
    }

    if (value == node->data) {
      return node;
    } else if (value < node->data) {
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

private:
  std::unique_ptr<Node> root_{nullptr};
};

} // namespace bst
} // namespace tree