#pragma once
#include <functional>
#include <memory>

namespace tree {
namespace avl {

template <typename T> class AVL final {
  struct Node {
    T data;
    int height{1};
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
  bool is_avl() const { return (check_balance(root_.get()) != -1); }

  ~AVL() { clear(); }

private:
  int get_height(Node *node) const { return node ? node->height : 0; }

  int get_balance(Node *node) const {
    return node ? (get_height(node->left.get()) - get_height(node->right.get()))
                : 0;
  }

  void update_height(Node *node) const {
    if (!node) {
      return;
    }

    node->height = 1 + std::max(get_height(node->left.get()),
                                get_height(node->right.get()));
  }

  std::unique_ptr<Node> rotate_right(std::unique_ptr<Node> b) {
    std::unique_ptr<Node> a = std::move(b->left);
    b->left = std::move(a->right);
    update_height(b.get());
    a->right = std::move(b);
    update_height(a.get());
    return a;
  }

  std::unique_ptr<Node> rotate_left(std::unique_ptr<Node> a) {
    std::unique_ptr<Node> b = std::move(a->right);
    a->right = std::move(b->left);
    update_height(a.get());
    b->left = std::move(a);
    update_height(b.get());
    return b;
  }

  std::unique_ptr<Node> balance_tree(std::unique_ptr<Node> node) {
    update_height(node.get());
    int balance = get_balance(node.get());

    // перевес слева
    if (balance > 1) {
      if (get_balance(node->left.get()) < 0) {
        node->left = rotate_left(std::move(node->left));
      }
      return rotate_right(std::move(node));
    }

    // перевес справа
    if (balance < -1) {
      if (get_balance(node->right.get()) > 0) {
        node->right = rotate_right(std::move(node->right));
      }
      return rotate_left(std::move(node));
    }

    return node;
  }

  int check_balance(Node *node) const {
    if (!node) {
      return 0;
    }

    int left_height = check_balance(node->left.get());
    if (left_height == -1) {
      return -1;
    }

    int right_height = check_balance(node->right.get());
    if (right_height == -1) {
      return -1;
    }

    if (std::abs(left_height - right_height) > 1) {
      return -1;
    }

    int height = 1 + std::max(left_height, right_height);
    return height;
  }

private:
  std::unique_ptr<Node> insert(std::unique_ptr<Node> node, T value) {
    if (!node) {
      return std::make_unique<Node>(value);
    }

    if (value < node->data) {
      node->left = insert(std::move(node->left), value);
    } else if (value > node->data) {
      node->right = insert(std::move(node->right), value);
    } else {
      return node;
    }

    return balance_tree(std::move(node));
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
    return balance_tree(std::move(node));
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

  Node *find_min(Node *node) const {
    while (node && node->left) {
      node = node->left.get();
    }
    return node;
  }

  void clear() {
    if (!root_) {
      return;
    }

    std::vector<std::unique_ptr<Node>> stack;
    stack.push_back(std::move(root_));

    while (!stack.empty()) {
      auto curr = std::move(stack.back());
      stack.pop_back();

      if (curr->left) {
        stack.push_back(std::move(curr->left));
      }

      if (curr->right) {
        stack.push_back(std::move(curr->right));
      }
    }
  }

private:
  std::unique_ptr<Node> root_{nullptr};
};

} // namespace avl
} // namespace tree