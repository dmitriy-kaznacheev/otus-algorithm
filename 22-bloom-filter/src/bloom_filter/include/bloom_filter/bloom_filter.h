#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace bf {

class BloomFilter {
public:
  BloomFilter(size_t capacity, double error_rate);

  void insert(const std::string &element);
  bool contains(const std::string &element) const;

  size_t bit_size() const { return m_; }
  size_t hash_count() const { return k_; }

private:
  struct HashPair {
    size_t h1;
    size_t h2;
  };
  HashPair hash_pair(const std::string &element) const;

private:
  size_t m_; // размер битового массива
  size_t k_; // количество хеш-функций
  std::vector<bool> bits_;
};

} // namespace bf