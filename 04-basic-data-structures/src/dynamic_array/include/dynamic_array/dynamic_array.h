#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>

namespace basic_ds {

template <typename T, int Sum = 0, int Mult = 1> class LinearBuffer final {
public:
  LinearBuffer(size_t sz = 0)
      : mem_{sz == 0 ? nullptr : new T[sz]}, capacity_{sz} {}
  T &operator[](size_t index) & { return mem_[index]; }
  const T &operator[](size_t index) const & { return mem_[index]; }
  void realoc() {
    LinearBuffer tmp{capacity_ * Mult + Sum};
    std::copy(mem_.get(), mem_.get() + capacity_, tmp.mem_.get());
    std::swap(tmp, *this);
  }
  void shif_right(size_t index, size_t size) {
    if (capacity_ >= (size + 1)) {
      std::copy_backward(mem_.get() + index, mem_.get() + size,
                         mem_.get() + size + 1);
    }
  }
  void shif_left(size_t index, size_t size) {
    std::copy(mem_.get() + index + 1, mem_.get() + size, mem_.get() + index);
  }
  size_t capacity() const { return capacity_; }

private:
  std::unique_ptr<T[]> mem_;
  size_t capacity_;
};

template <typename T, typename Buffer> class DynamicArray final {
public:
  DynamicArray() : buf_{Buffer{}}, size_{0} {}
  void add(T item) { add(std::move(item), size_); }
  void add(T item, size_t index) {
    if (size_ == buf_.capacity()) {
      buf_.realoc();
    }
    buf_.shif_right(index, size_);
    buf_[index] = std::move(item);
    ++size_;
  }
  T remove(size_t index) {
    T tmp{buf_[index]};
    buf_.shif_left(index, size_);
    --size_;
    return tmp;
  }
  void dump(std::ostream &os) const {
    for (size_t i = 0; i != size_; ++i) {
      os << buf_[i] << ' ';
    }
    os << '\n';
  }
  T &operator[](size_t index) { return buf_[index]; }
  const T &operator[](size_t index) const { return buf_[index]; }
  size_t size() const { return size_; }

private:
  Buffer buf_;
  size_t size_;
};

} // namespace basic_ds
