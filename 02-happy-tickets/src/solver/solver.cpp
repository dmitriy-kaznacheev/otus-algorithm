#include "solver/solver.h"
#include <cassert>
#include <numeric>
#include <stdexcept>

namespace solver {

HappyTickets::HappyTickets(long n) : n_{n} {
  if ((n < 1) || (n > 10)) {
    throw std::invalid_argument("the value should be between 1 and 10");
  }
}

long HappyTickets::run() const {
  Column column(block_size, 1);

  for (int _ = 1; _ != n_; ++_) {
    column = get_next_column(std::move(column));
  }

  return std::transform_reduce(std::begin(column), std::end(column), 0l,
                               std::plus{}, [](auto val) { return val * val; });
}

Column HappyTickets::get_next_column(Column prev_column) const {
  Column column(prev_column.size() + block_size - 1, 0);
  for (int i = 0; i != column.size(); ++i) {
    long sum_inside_block{};
    for (int j = 0; j != block_size; ++j) {
      auto k{i - j};
      if ((k >= 0) && (k < prev_column.size())) {
        sum_inside_block += prev_column[k];
      }
    }
    column[i] = sum_inside_block;
  }
  return column;
}

} // namespace solver