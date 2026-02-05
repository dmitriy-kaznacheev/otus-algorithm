#pragma once

namespace solver {

class HappyTickets final {
public:
  HappyTickets(long n);
  long run() const;

private:
  long n_;
};

} // namespace solver