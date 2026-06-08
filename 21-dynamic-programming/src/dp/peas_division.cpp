#include <dp/peas_division.h>
#include <stdexcept>

namespace dp {

std::string sum_fractions(const std::string &expression) {
  size_t slash1 = expression.find('/');
  size_t plus = expression.find('+');
  size_t slash2 = expression.find('/', plus);

  if (slash1 == std::string::npos || plus == std::string::npos ||
      slash2 == std::string::npos) {
    throw std::invalid_argument("Invalid format: expected a/b+c/d");
  }

  int a = std::stoi(expression.substr(0, slash1));
  int b = std::stoi(expression.substr(slash1 + 1, plus - slash1 - 1));
  int c = std::stoi(expression.substr(plus + 1, slash2 - plus - 1));
  int d = std::stoi(expression.substr(slash2 + 1));

  int num = a * d + c * b;
  int den = b * d;

  int g = std::gcd(num, den);
  num /= g;
  den /= g;

  return std::to_string(num) + "/" + std::to_string(den);
}

} // namespace dp
