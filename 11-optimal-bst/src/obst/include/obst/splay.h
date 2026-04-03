#pragma once
#include <functional>
#include <memory>

namespace tree {
namespace splay {

template <typename T> class Splay final {
  struct Node {
    T data{};
    std::shared_ptr<Node> left{nullptr};
    std::shared_ptr<Node> right{nullptr};
    std::weak_ptr<Node> parent{};
  };

public:
  void insert(T value) {
    if (!root_) {
      root_ = std::make_shared<Node>(std::move(value));
      return;
    }

    auto curr = root_;
    std::shared_ptr<Node> last = nullptr;

    while (curr) {
      last = curr;
      if (value == curr->data) {
        splay(curr);
        return;
      }
      curr = (value < curr->data) ? curr->left : curr->right;
    }

    auto new_node = std::make_shared<Node>(std::move(value));
    new_node->parent = last;

    if (new_node->data < last->data) {
      last->left = new_node;
    } else {
      last->right = new_node;
    }

    splay(new_node);
  }

  bool search(const T &value) {
    auto curr = root_;
    std::shared_ptr<Node> last = nullptr;

    while (curr) {
      last = curr;
      if (value == curr->data) {
        splay(curr);
        return true;
      }
      curr = (value < curr->data) ? curr->left : curr->right;
    }

    if (last) {
      splay(last);
    }
    return false;
  }

  void remove(const T &value) {
    if (!search(value)) {
      return;
    }

    auto old_root = root_;
    auto left_subtree = old_root->left;
    auto right_subtree = old_root->right;

    if (left_subtree) {
      left_subtree->parent.reset();
    }
    if (right_subtree) {
      right_subtree->parent.reset();
    }

    if (!left_subtree) {
      root_ = right_subtree;
    } else if (!right_subtree) {
      root_ = left_subtree;
    } else {

      auto max_in_left = left_subtree;
      while (max_in_left->right) {
        max_in_left = max_in_left->right;
      }

      splay(max_in_left);

      root_->right = right_subtree;
      if (right_subtree) {
        right_subtree->parent = root_;
      }
    }
  }

  void traverse(std::function<void(T)> visit) const {
    inorder_traverse(root_, visit);
  }

  bool is_valid_bst() const {
    return is_valid_bst_helper(root_, nullptr, nullptr);
  }

  ~Splay() { clear(); }

private:
  bool is_valid_bst_helper(std::shared_ptr<Node> node, const T *min_val,
                           const T *max_val) const {
    if (!node) {
      return true;
    }

    if ((min_val && node->data <= *min_val) ||
        (max_val && node->data >= *max_val)) {
      return false;
    }

    return is_valid_bst_helper(node->left, min_val, &node->data) &&
           is_valid_bst_helper(node->right, &node->data, max_val);
  }

  void rotate_right(std::shared_ptr<Node> node) {
    if (!node || !node->left) {
      return;
    }

    auto new_root = node->left;
    node->left = new_root->right;
    if (node->left) {
      node->left->parent = node;
    }
    new_root->parent = node->parent;
    auto parent = node->parent.lock();

    if (!parent) {
      root_ = new_root;
    } else if (node == parent->left) {
      parent->left = new_root;
    } else {
      parent->right = new_root;
    }

    new_root->right = node;
    node->parent = new_root;
  }

  void rotate_left(std::shared_ptr<Node> node) {
    if (!node || !node->right) {
      return;
    }

    auto new_root = node->right;
    node->right = new_root->left;
    if (node->right) {
      node->right->parent = node;
    }

    new_root->parent = node->parent;
    auto parent = node->parent.lock();

    if (!parent) {
      root_ = new_root;
    } else if (node == parent->left) {
      parent->left = new_root;
    } else {
      parent->right = new_root;
    }

    new_root->left = node;
    node->parent = new_root;
  }

  void splay(std::shared_ptr<Node> node) {
    if (!node) {
      return;
    }

    while (auto parent = node->parent.lock()) {
      auto grandparent = parent->parent.lock();
      if (!grandparent) {
        // zig
        if (parent->left == node)
          rotate_right(parent);
        else
          rotate_left(parent);
      } else {
        if (parent->left == node && grandparent->left == parent) {
          // zig-zig
          rotate_right(grandparent);
          rotate_right(parent);
        } else if (parent->right == node && grandparent->right == parent) {
          // zig-zig
          rotate_left(grandparent);
          rotate_left(parent);
        } else if (parent->left == node && grandparent->right == parent) {
          // zig-zag
          rotate_right(parent);
          rotate_left(grandparent);
        } else {
          // zig-zag
          rotate_left(parent);
          rotate_right(grandparent);
        }
      }
    }
    root_ = node;
  }

  void inorder_traverse(std::shared_ptr<Node> node,
                        std::function<void(T)> visit) const {
    if (!node) {
      return;
    }

    inorder_traverse(node->left, visit);
    visit(node->data);
    inorder_traverse(node->right, visit);
  }

  void clear() {
    if (!root_) {
      return;
    }

    std::vector<std::shared_ptr<Node>> stack;
    stack.push_back(std::move(root_));

    while (!stack.empty()) {
      auto curr = std::move(stack.back());
      stack.pop_back();

      curr->parent.reset();

      if (curr->left) {
        stack.push_back(std::move(curr->left));
      }

      if (curr->right) {
        stack.push_back(std::move(curr->right));
      }
    }
  }

private:
  std::shared_ptr<Node> root_{nullptr};
};

} // namespace splay
} // namespace tree
