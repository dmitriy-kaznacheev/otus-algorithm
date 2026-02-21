#pragma once
#include <vector>

namespace solver {

using Column = std::vector<long>;

class HappyTickets final {
public:
  HappyTickets(long n);
  long run() const;

private:
  Column get_next_column(Column prev_column) const;

private:
  static constexpr int block_size{10};
  long n_;
};

} // namespace solver