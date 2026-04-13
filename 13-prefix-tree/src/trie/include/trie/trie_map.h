
#pragma once
#include <algorithm>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace trie {

template <typename K = char, typename V = std::string> class TrieMap final {
  struct Node {
    struct Child {
      K key;
      std::unique_ptr<Node> node;
    };
    std::vector<Child> children;
    std::optional<V> value;
  };

public:
  TrieMap() : root_{std::make_unique<Node>()} {}

  template <typename Sequence, typename Val>
  void insert(const Sequence &key, Val &&val) {
    Node *current = root_.get();
    for (const auto &sym : key) {
      auto it = std::find_if(current->children.begin(), current->children.end(),
                             [&sym](const auto &ch) { return ch.key == sym; });
      if (it == current->children.end()) {
        current->children.push_back({sym, std::make_unique<Node>()});
        current = current->children.back().node.get();
      } else {
        current = it->node.get();
      }
    }
    current->value = std::forward<Val>(val);
  }

  template <typename Sequence> bool remove(const Sequence &key) {
    return remove(root_.get(), key, 0);
  }

  template <typename Sequence> V *get(const Sequence &key) {
    Node *current = root_.get();
    for (const auto &sym : key) {
      auto it = std::find_if(current->children.begin(), current->children.end(),
                             [&sym](const auto &ch) { return ch.key == sym; });
      if (it == current->children.end()) {
        return nullptr;
      } else {
        current = it->node.get();
      }
    }
    return current->value ? &(*current->value) : nullptr;
  }

private:
  template <typename Sequence>
  bool remove(Node *current, const Sequence &key, size_t depth) {
    if (!current) {
      return false;
    }

    if (depth == key.size()) {
      if (!current->value) {
        return false;
      }
      current->value.reset();
      return current->children.empty();
    }

    const auto &sym = key[depth];
    auto it = std::find_if(current->children.begin(), current->children.end(),
                           [&sym](const auto &ch) { return ch.key == sym; });
    if (it != current->children.end()) {
      bool should_delete_child = remove(it->node.get(), key, depth + 1);
      if (should_delete_child) {
        current->children.erase(it);
        return !current->value && current->children.empty();
      }
    }
    return false;
  }

private:
  std::unique_ptr<Node> root_;
};

} // namespace trie