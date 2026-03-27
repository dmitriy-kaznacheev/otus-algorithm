#pragma once
#include <vector>

namespace hash {
namespace opena {

template <typename K, typename V> class Table final {
public:
  explicit Table(size_t size = 13) : capacity_{size} {}

private:
  size_t capacity_;
};

} // namespace opena
} // namespace hash