#pragma once
#include <algorithm>
#include <forward_list>
#include <optional>
#include <utility>
#include <vector>

namespace sort {
namespace bucket {

namespace detail {
template <typename T> class Bucket final {
  using Chain = std::forward_list<T>;
  using ChainIt = typename Chain::iterator;
  using Data = std::vector<Chain>;

public:
  template <typename It> Bucket(It first, It last) {
    if (first == last) {
      return;
    }

    auto count = std::distance(first, last);
    auto max = *std::max_element(first, last);

    data_.resize(count);
    for (auto it = first; it != last; ++it) {
      T value = *it;
      size_t index = (value * count) / (max + 1);
      insert_sorted(index, value);
    }
  }

  class Iterator final {
  public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;

  public:
    Iterator(Bucket::Data *pdata = nullptr) : pdata_{pdata} {
      if (pdata_ == nullptr) {
        return;
      }

      if (!pdata_->empty()) {
        it_ = (*pdata)[0].begin();
      }

      skip_empty();
    }

    reference operator*() const { return *it_.value(); }
    pointer operator->() { return &(*it_.value()); }

    Iterator &operator++() {
      ++it_.value();
      skip_empty();
      return *this;
    }

    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    bool operator==(const Iterator &rhs) const {
      bool lhs_end = !it_.has_value() || (idata_ == pdata_->size());
      bool rhs_end = !rhs.it_.has_value() || (rhs.idata_ == rhs.pdata_->size());

      return (lhs_end && rhs_end) ||
             ((idata_ == rhs.idata_) && (it_ == rhs.it_));
    }
    bool operator!=(const Iterator &rhs) const { return !(*this == rhs); }

  private:
    void skip_empty() {
      while ((idata_ < pdata_->size()) && (it_ == (*pdata_)[idata_].end())) {
        ++idata_;
        if (idata_ < pdata_->size()) {
          it_ = (*pdata_)[idata_].begin();
        }
      }
    }

  private:
    Bucket::Data *pdata_{nullptr};
    std::optional<Bucket::ChainIt> it_{std::nullopt};
    size_t idata_{0};
  }; // Iterator

  Iterator begin() { return Iterator{&data_}; }
  Iterator end() { return Iterator{}; }

private:
  void insert_sorted(size_t index, T value) {
    auto before_pos = data_[index].before_begin();
    auto current_pos = data_[index].begin();

    while ((current_pos != data_[index].end()) && (*current_pos < value)) {
      before_pos = current_pos;
      ++current_pos;
    }

    data_[index].insert_after(before_pos, value);
  }

private:
  Data data_;
};

template <typename It>
Bucket(It, It) -> Bucket<typename std::iterator_traits<It>::value_type>;

} // namespace detail

template <typename It> void sort(It first, It last) {
  using namespace detail;
  Bucket bucket{first, last};
  std::move(bucket.begin(), bucket.end(), first);
}

} // namespace bucket
} // namespace sort