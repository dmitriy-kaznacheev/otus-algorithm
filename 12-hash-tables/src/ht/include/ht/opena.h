#pragma once
#include <memory>
#include <optional>
#include <vector>

namespace hash {
namespace opena {

template <typename K, typename V> class Table final {
  enum class State { Empty, Occupied, Deleted };
  struct Entry {
    K key{};
    V value{};
    State state{State::Empty};
  };

public:
  explicit Table(size_t size = 13) : capacity_{size} { table_.resize(size); }

  bool insert(K key, V value) {
    if (size_ > (capacity_ / 2)) {
      rehash();
    }

    auto h = hash(key);
    for (size_t i = 0; i != capacity_; ++i) {
      size_t index = (h + i * i) % capacity_;

      if (!table_[index] || (table_[index]->state != State::Occupied)) {
        table_[index] = std::make_unique<Entry>(
            std::move(key), std::move(value), State::Occupied);
        ++size_;
        return true;
      }

      if ((table_[index]->key == key) &&
          (table_[index]->state != State::Occupied)) {
        table_[index]->value = std::move(value);
        return true;
      }
    }

    return false;
  }

  std::optional<V> get(const K &key) const {
    auto h = hash(key);
    for (size_t i = 0; i != capacity_; ++i) {
      size_t index = (h + i * i) % capacity_;

      if (!table_[index] || (table_[index]->state == State::Empty)) {
        return std::nullopt;
      }

      if ((table_[index]->key == key) &&
          (table_[index]->state == State::Occupied)) {
        return table_[index]->value;
      }
    }

    return std::nullopt;
  }

  bool remove(const K &key) {
    auto h = hash(key);
    for (size_t i = 0; i != capacity_; ++i) {
      size_t index = (h + i * i) % capacity_;

      if (!table_[index] || (table_[index]->state == State::Empty)) {
        return false;
      }

      if ((table_[index]->key == key) &&
          (table_[index]->state == State::Occupied)) {
        table_[index]->state = State::Deleted;
        --size_;
        return true;
      }
    }

    return false;
  }

  void rehash() {
    size_t new_capacity = capacity_ * 2;
    Table table{new_capacity};
    for (auto &entry : table_) {
      if (entry && (entry->state == State::Occupied)) {
        table.insert(std::move(entry->key), std::move(entry->value));
      }
    }
    std::swap(table, *this);
  }

private:
  size_t hash(const K &key) const { return std::hash<K>{}(key) % capacity_; }

private:
  std::vector<std::unique_ptr<Entry>> table_;
  size_t capacity_;
  size_t size_{0};
};

} // namespace opena
} // namespace hash