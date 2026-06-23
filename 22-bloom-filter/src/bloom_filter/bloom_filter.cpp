#include <bloom_filter/bloom_filter.h>

#include <cmath>
#include <functional>
#include <stdexcept>

namespace bf {

BloomFilter::BloomFilter(size_t capacity, double error_rate) {
  if (capacity == 0 || error_rate <= 0.0 || error_rate >= 1.0) {
    throw std::invalid_argument("Invalid BloomFilter parameters");
  }

  double ln2 = std::log(2.0);
  m_ = static_cast<size_t>(-(capacity * std::log(error_rate)) / (ln2 * ln2));
  k_ = static_cast<size_t>((static_cast<double>(m_) / capacity) * ln2);

  k_ = std::max(k_, static_cast<size_t>(1));
  m_ = std::max(m_, static_cast<size_t>(1));

  bits_.resize(m_, false);
}

BloomFilter::HashPair BloomFilter::hash_pair(const std::string &element) const {
  std::hash<std::string> hasher;
  return {hasher(element), hasher(element + "_salt")};
}

void BloomFilter::insert(const std::string &element) {
  auto [h1, h2] = hash_pair(element);
  for (size_t i = 0; i < k_; ++i) {
    size_t idx = (h1 + i * h2) % m_;
    bits_[idx] = true;
  }
}

bool BloomFilter::contains(const std::string &element) const {
  auto [h1, h2] = hash_pair(element);
  for (size_t i = 0; i < k_; ++i) {
    size_t idx = (h1 + i * h2) % m_;
    if (!bits_[idx]) {
      return false;
    }
  }
  return true;
}

} // namespace bf