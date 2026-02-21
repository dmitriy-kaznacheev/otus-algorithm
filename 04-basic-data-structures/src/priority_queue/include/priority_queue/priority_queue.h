#pragma once
#include "dynamic_array/dynamic_array.h"
#include <algorithm>

namespace basic_ds {

template <typename T> using Array = DynamicArray<T, LinearBuffer<T, 1, 2>>;

template <typename T> class PriorityQueue final {
  struct Data {
    T data;
    int weight;
  };

public:
  void enqueue(int priority, T item) { data_.add(Data{item, priority}); }
  T dequeue() {
    if (data_.size() < 1) {
      throw std::runtime_error("queue is empty");
    }

    Data max = data_[0];
    size_t index = 0;
    for (size_t i = 0; i != data_.size(); ++i) {
      if (data_[i].weight > max.weight) {
        max = data_[i];
        index = i;
      }
    }
    data_.remove(index);
    return max.data;
  }

private:
  Array<Data> data_;
};

} // namespace basic_ds
