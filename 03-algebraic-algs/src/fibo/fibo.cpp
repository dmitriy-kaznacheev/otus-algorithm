#include "fibo/fibo.h"
#include <array>
#include <cmath>
#include <utility>

namespace fibo {

unsigned long fib_recu(unsigned n) {
  if (n < 2) {
    return n;
  }

  return fib_recu(n - 1) + fib_recu(n - 2);
}

unsigned long fib_iter(unsigned n) {
  if (n < 2) {
    return n;
  }

  unsigned long a{1}, b{1};
  for (int i = 2; i != n; ++i) {
    a = std::exchange(b, a + b);
  }
  return b;
}

unsigned long fib_gold(unsigned n) {
  double phi = (1. + std::sqrt(5.)) / 2.;
  return std::round(std::pow(phi, n) / std::sqrt(5.));
}

namespace {

constexpr size_t SZ = 2;
using MatrixRow = std::array<unsigned long, SZ>;
using Matrix = std::array<MatrixRow, SZ>;

Matrix matrix_multiply(Matrix a, Matrix b) {
  Matrix c{MatrixRow{0, 0}, MatrixRow{0, 0}};
  for (int i = 0; i != SZ; ++i) {
    for (int j = 0; j != SZ; ++j) {
      for (int k = 0; k != SZ; ++k) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }

  return c;
}

Matrix matrix_pow(Matrix m, unsigned long exp) {
  Matrix res{MatrixRow{1, 0}, MatrixRow{0, 1}};

  while (exp > 0) {
    if (exp & 1) {
      res = matrix_multiply(std::move(res), m);
    }
    m = matrix_multiply(m, m);
    exp >>= 1;
  }
  return res;
}

} // namespace

unsigned long fib_mtrx(unsigned n) {
  if (n == 0) {
    return 0;
  }

  Matrix m{MatrixRow{1, 1}, MatrixRow{1, 0}};
  m = matrix_pow(std::move(m), n - 1);
  return m[0][0];
}

} // namespace fibo