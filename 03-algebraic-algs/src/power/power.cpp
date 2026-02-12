#include "power/power.h"

namespace power {

double itr_pow(double base, unsigned long exp) {
  double res = 1.;
  for (int i = 0; i != exp; ++i) {
    res *= base;
  }
  return res;
}

double two_pow(double base, unsigned long exp) {
  double res = 1.;
  while (exp > 0) {
    if ((exp % 2) == 1) {
      res *= base;
    }
    base *= base;
    exp /= 2;
  }
  return res;
}

double bin_pow(double base, unsigned long exp) {
  double res = 1.;
  while (exp > 0) {
    if (exp & 1) {
      res *= base;
    }
    base *= base;
    exp >>= 1;
  }
  return res;
}

} // namespace power