#include "primes/primes.h"
#include <cstdint>
#include <numeric>
#include <vector>

namespace primes {

bool is_prime_full(unsigned n) {
  unsigned count = 0;
  for (unsigned i = 1; i <= n; ++i) {
    if ((n % i) == 0) {
      ++count;
    }
  }
  return (count == 2);
}

bool is_prime_break(unsigned n) {
  for (unsigned i = 2; i < n; ++i) {
    if ((n % i) == 0) {
      return false;
    }
  }
  return true;
}

bool is_prime_odd(unsigned n) {
  if ((n % 2) == 0) {
    return (n == 2);
  }
  for (unsigned i = 3; i < n; i += 2) {
    if ((n % i) == 0) {
      return false;
    }
  }
  return true;
}

bool is_prime_sqrt(unsigned n) {
  if ((n % 2) == 0) {
    return (n == 2);
  }
  for (unsigned i = 3; i * i <= n; i += 2) {
    if ((n % i) == 0) {
      return false;
    }
  }
  return true;
}

unsigned count_primes(unsigned n, UnaryPredicate pred) {
  unsigned count = 0;
  for (unsigned i = 2; i <= n; ++i) {
    if (pred(i)) {
      ++count;
    }
  }
  return count;
}

unsigned eratosthenes(unsigned n) {
  // std::vector<bool> prime(n + 1, true); // по одному биту на элемент

  std::vector<int> prime(n + 1, 1);
  prime[0] = prime[1] = 0;

  for (size_t i = 2; i * i <= n; ++i) {
    if (prime[i] == 1) {
      for (size_t j = i * i; j <= n; j += i) {
        prime[j] = 0;
      }
    }
  }
  return std::reduce(std::begin(prime), std::end(prime));
}

namespace {
void clear_bit(std::vector<uint32_t> &v, size_t bit) {
  size_t index = (bit >> 5);
  v[index] &= ~(1U << (bit & 31));
}

void set_bit(std::vector<uint32_t> &v, size_t bit) {
  size_t index = (bit >> 5);
  v[index] |= (1U << (bit & 31));
}

bool get_bit(const std::vector<uint32_t> &v, size_t bit) {
  size_t index = (bit >> 5);
  return (v[index] & (1U << (bit & 31))) != 0;
}

unsigned count_bit(uint32_t value) {
  unsigned count = 0;
  while (value > 0) {
    count += (value & 1);
    value >>= 1;
  }
  return count;
}
} // namespace

unsigned eratosthenes_bit(unsigned n) {
  // std::vector<bool> prime(n + 1, true); // по одному биту на элемент

  std::vector<uint32_t> prime((n >> 5) + 1, 0xFFFFFFFF); // (n/32 + 1)
  {
    // занулить остаток массива
    size_t begin = n + 1;
    size_t end = prime.size() * (1 << 5);
    for (size_t i = begin; i != end; ++i) {
      clear_bit(prime, i);
    }
  }

  // 0 и 1 не простые
  clear_bit(prime, 0);
  clear_bit(prime, 1);

  for (size_t i = 2; i * i <= n; ++i) {
    if (get_bit(prime, i) == true) {
      for (size_t j = i * i; j <= n; j += i) {
        clear_bit(prime, j);
      }
    }
  }
  return std::transform_reduce(std::begin(prime), std::end(prime), 0U,
                               std::plus{}, count_bit);
}

unsigned eratosthenes_fast(unsigned n) { 
  std::vector<int> min_prime(n + 1, 0); 
  std::vector<int> prime;
  prime.reserve(n + 1);

  for (size_t i = 2; i <= n; ++i) {
    if (min_prime[i] == 0) {
      min_prime[i] = i;
      prime.push_back(i);
    }
    for (size_t j = 0; (j < prime.size()) && (prime[j] <= min_prime[i]) && (i * prime[j] <= n); ++j) {
      min_prime[i * prime[j]] = prime[j];
    }
  }
  return prime.size();
}

} // namespace primes