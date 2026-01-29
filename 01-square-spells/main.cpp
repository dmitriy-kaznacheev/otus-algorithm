#include <functional>
#include <iostream>

constexpr int N = 25;
using BinaryPredicate = std::function<bool(int, int)>;

void draw(BinaryPredicate pred) {
  for (int y = 0; y != N; ++y) {
    for (int x = 0; x != N; ++x) {
      std::cout << (pred(x, y) ? '#' : '.') << ' ';
    }
    std::cout << '\n';
  }
  std::cout << std::endl;
}

void solution_01() {
  std::cout << "01\n";
  draw([](int x, int y) { return x > y; });
}

void solution_02() {
  std::cout << "02\n";
  draw([](int x, int y) { return x == y; });
}

void solution_03() {
  std::cout << "03\n";
  draw([](int x, int y) { return x == (N - y - 1); });
}

void solution_04() {
  std::cout << "04\n";
  draw([](int x, int y) { return (x - 5) <= (N - y - 1); });
}

void solution_05() {
  std::cout << "05\n";
  draw([](int x, int y) { return (x == (2 * y)) || (x == (2 * y + 1)); });
}

int main() {
  solution_01();
  solution_02();
  solution_03();
  solution_04();
  solution_05();

  return 0;
}
