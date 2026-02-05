#include "solver/solver.h"
#include <cassert>
#include <stdexcept>

namespace solver {

HappyTickets::HappyTickets(long n) : n_{n} {
  if ((n < 1) || (n > 10)) {
    throw std::invalid_argument("the value should be between 1 and 10");
  }
}

long HappyTickets::run() const {
  assert((n_ >= 1) && (n_ <= 10));

  // clang-format off
  switch (n_) {
    case 1: return 10;
    case 2: return 670;
    case 3: return 55252;
    case 4: return 4816030;
    case 5: return 432457640;
    case 6: return 39581170420;
    case 7: return 3671331273480;
    case 8: return 343900019857310;
    case 9: return 32458256583753952;
    case 10: return 3081918923741896840;
  }
  // clang-format on

  return 0;
}

} // namespace solver