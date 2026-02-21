#pragma once
#include "dynamic_array/dynamic_array.h"
#include <optional>

namespace basic_ds {

template <typename T> using Array = DynamicArray<T, LinearBuffer<T, 1, 2>>;

template <typename T> class SparceArray final {
  struct Data {
    T data;
    size_t index;
  };

public:
  void add(T item, size_t index) { data_.add(Data{item, index}); }
  std::optional<T> operator[](size_t index) const {
    for (size_t i = 0; i != data_.size(); ++i) {
      if (data_[i].index == index) {
        return data_[i].data;
      }
    }
    return std::nullopt;
  }

private:
  Array<Data> data_;
};

} // namespace basic_ds
