#pragma once
#include <functional>

namespace primes {

using UnaryPredicate = std::function<bool(unsigned)>;

bool is_prime_full(unsigned n);
bool is_prime_break(unsigned n);
bool is_prime_odd(unsigned n);
bool is_prime_sqrt(unsigned n);

unsigned count_primes(unsigned n, UnaryPredicate pred);
unsigned eratosthenes(unsigned n);
unsigned eratosthenes_bit(unsigned n);
unsigned eratosthenes_fast(unsigned n);

} // namespace primes