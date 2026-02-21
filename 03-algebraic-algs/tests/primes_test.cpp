#include "algebraic_test.h"
#include "primes/primes.h"
#include "utils.h"

template <typename V, typename R>
void is_prime_full_test(V n, R expected, int test_index) {
  Timer t;
  auto actual = primes::count_primes(n, primes::is_prime_full);
  show_result(actual, expected, test_index, t.duration_ns(), " prime_full"sv);
}

template <typename V, typename R>
void is_prime_break_test(V n, R expected, int test_index) {
  Timer t;
  auto actual = primes::count_primes(n, primes::is_prime_break);
  show_result(actual, expected, test_index, t.duration_ns(), "prime_break"sv);
}

template <typename V, typename R>
void is_prime_odd_test(V n, R expected, int test_index) {
  Timer t;
  auto actual = primes::count_primes(n, primes::is_prime_odd);
  show_result(actual, expected, test_index, t.duration_ns(), "  prime_odd"sv);
}

template <typename V, typename R>
void is_prime_sqrt_test(V n, R expected, int test_index) {
  Timer t;
  auto actual = primes::count_primes(n, primes::is_prime_sqrt);
  show_result(actual, expected, test_index, t.duration_ns(), " prime_sqrt"sv);
}

template <typename V, typename R>
void eratosthenes_test(V n, R expected, int test_index) {
  Timer t;
  auto actual = primes::eratosthenes(n);
  show_result(actual, expected, test_index, t.duration_ns(), "      sieve"sv);
}

template <typename V, typename R>
void eratosthenes_bit_test(V n, R expected, int test_index) {
  Timer t;
  auto actual = primes::eratosthenes_bit(n);
  show_result(actual, expected, test_index, t.duration_ns(), "  sieve_bit"sv);
}

template <typename V, typename R>
void eratosthenes_fast_test(V n, R expected, int test_index) {
  Timer t;
  auto actual = primes::eratosthenes_fast(n);
  show_result(actual, expected, test_index, t.duration_ns(), " sieve_fast"sv);
}

void primes_test() {
  std::cout << "--- prime number tests ---"sv << std::endl;

  for (int i = 0;; ++i) {
    auto [ipath, opath] = get_file_paths("primes"s, i);
    auto in = get_file_content1<unsigned>(std::move(ipath));
    auto out = get_file_content1<unsigned>(std::move(opath));

    if (!in || !out) {
      break;
    }

    auto n = in.value();
    auto expected = out.value();

    is_prime_full_test(n, expected, i);
    is_prime_break_test(n, expected, i);
    is_prime_odd_test(n, expected, i);
    is_prime_sqrt_test(n, expected, i);
    eratosthenes_test(n, expected, i);
    eratosthenes_bit_test(n, expected, i);
    eratosthenes_fast_test(n, expected, i);
  }

  std::cout << std::endl;
}