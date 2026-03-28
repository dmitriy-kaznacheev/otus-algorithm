
#pragma once
#include <memory>
#include <optional>
#include <utility>
#include <vector>

namespace hash {
namespace chain {

template <typename K, typename V> class Table final {
  struct Node {
    K key{};
    V value{};
    std::unique_ptr<Node> next{nullptr};
  };

  using NodePair = struct {
    Node *prev{nullptr}, *curr{nullptr};
  };

public:
  explicit Table(size_t size = 13) : capacity_{size} { buckets_.resize(size); }

  bool insert(K key, V value) {
    auto cur_node = find(key).curr;
    if (cur_node) {
      cur_node->value = std::move(value);
    } else {
      size_t index = get_index(key);
      auto new_node = std::make_unique<Node>(std::move(key), std::move(value),
                                             std::move(buckets_[index]));
      buckets_[index] = std::move(new_node);
      ++size_;
    }

    return true;
  }

  std::optional<V> get(const K &key) const {
    auto cur_node = find(key).curr;
    return cur_node ? std::make_optional(cur_node->value) : std::nullopt;
  }

  bool remove(const K &key) {
    auto [prev, curr] = find(key);

    if (!curr) {
      return false;
    }

    if (prev) {
      prev->next = std::move(curr->next);
    } else {
      size_t index = get_index(key);
      buckets_[index] = std::move(curr->next);
    }
    --size_;
    return true;
  }

  void rehash() {
    auto load_factor = get_load_factor();
    if (max_load_factor_ > load_factor) {
      return;
    }

    size_t new_capacity = capacity_ * static_cast<size_t>(load_factor + 1);
    Table ht{new_capacity};
    for (auto &curr_node : buckets_) {
      while (curr_node) {
        auto next_node = std::move(curr_node->next);
        ht.insert(std::move(curr_node->key), std::move(curr_node->value));
        curr_node = std::move(next_node);
      }
    }
    std::swap(ht, *this);
  }

private:
  NodePair find(const K &key) const {
    size_t index = get_index(key);

    Node *curr = buckets_[index].get();
    Node *prev = nullptr;

    while (curr) {
      if (curr->key == key) {
        return {prev, curr};
      }
      prev = std::exchange(curr, curr->next.get());
    }

    return {nullptr, nullptr};
  }

  size_t get_index(const K &key) const {
    return std::hash<K>{}(key) % capacity_;
  }

  float get_load_factor() const {
    return (static_cast<float>(size_) / capacity_);
  }

private:
  std::vector<std::unique_ptr<Node>> buckets_;
  size_t capacity_;
  size_t size_{0};
  float max_load_factor_{1.0f};
};

} // namespace chain
} // namespace hash