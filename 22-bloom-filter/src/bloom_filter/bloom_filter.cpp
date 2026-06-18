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

std::vector<size_t> BloomFilter::get_hashes(const std::string &element) const {
  std::hash<std::string> hasher;
  size_t h1 = hasher(element);
  size_t h2 = hasher(element + "_salt");

  // генерирует k_ индексов через double hashing:
  std::vector<size_t> hashes(k_);
  std::generate_n(hashes.begin(), k_,
                  [&, i = 0]() mutable { return (h1 + i++ * h2) % m_; });
  return hashes;
}

void BloomFilter::insert(const std::string &element) {
  auto hashes = get_hashes(element);
  std::for_each(hashes.begin(), hashes.end(),
                [this](size_t idx) { bits_[idx] = true; });
}

bool BloomFilter::contains(const std::string &element) const {
  auto hashes = get_hashes(element);
  return std::all_of(hashes.begin(), hashes.end(),
                     [this](size_t idx) { return bits_[idx]; });
}

} // namespace bf