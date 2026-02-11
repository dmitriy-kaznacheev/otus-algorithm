#include "gcd/gcd.h"
#include <utility>

namespace gcd {

long euclidean_sub(long a, long b) {
  while (a != b) {
    if (a > b) {
      a = a - b;
    } else {
      b = b - a;
    }
  }
  return a;
}

long euclidean_div(long a, long b) {
  while (b != 0) {
    a = std::exchange(b, a % b);
  }
  return a;
}

long binary_stein(long a, long b) {
  if (a == 0) {
    return b;
  }

  if (b == 0) {
    return a;
  }

  // найти первый общий делитель 2^shift
  int shift = 0;
  {
    while (((a | b) & 1) == 0) {
      a >>= 1;
      b >>= 1;
      ++shift;
    }
  }

  // пока a четное - делить на 2
  while ((a & 1) == 0) {
    a >>= 1;
  }

  while (b != 0) {

    // пока b четное - делить на 2
    while ((b & 1) == 0) {
      b >>= 1;
    }

    // из большего вычесть меньшее
    {
      if (a > b) {
        std::swap(a, b);
      }

      b = b - a;
    }
  }

  // умножить а на нужное кол-во 2
  return a << shift;
}

} // namespace gcd