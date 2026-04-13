
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
        it = std::prev(current->children.end());
      }
      current = it->node.get();
    }

    // TODO: проверка дубликатов — добавить логику:
    // 1. Проверить, существует ли уже значение для этого ключа
    // (current->value.has_value())
    // 2. Принять решение:
    //    - пропустить вставку, если ключ уже есть;
    //    - обновить значение, если это разрешено;
    //    - выбросить исключение или вернуть статус.

    current->value = std::forward<Val>(val);
  }

  template <typename Sequence> void remove(const Sequence &key) {
    // TODO: вернуть статус удаления ключа:
    // - true: ключ был найден и его значение удалено;
    // - false: ключ не найден в дереве.
    // Текущая реализация возвращает признак того,
    // должен ли узел быть удалён родителем
    // - true: узел пустой и подлежит удалению;
    // - false: узел нужно сохранить.
    remove(root_.get(), key, 0);
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