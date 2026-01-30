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

void solution_06() {
  std::cout << "06\n";
  draw([](int x, int y) { return (x < 10) || (y < 10); });
}

void solution_07() {
  std::cout << "07\n";
  draw([](int x, int y) { return (x > 15) && (y > 15); });
}

void solution_08() {
  std::cout << "08\n";
  draw([](int x, int y) { return (x < 1) || (y < 1); });
}

void solution_09() {
  std::cout << "09\n";
  draw([](int x, int y) { return (x > y + 10) || (y > x + 10); });
}

void solution_10() {
  std::cout << "10\n";
  draw([](int x, int y) { return (x > y) && (x < 2 * y + 2); });
}

void solution_11() {
  std::cout << "11\n";
  draw([](int x, int y) {
    return (x == 1) || (x == N - 2) || (y == 1) || (y == N - 2);
  });
}

void solution_12() {
  std::cout << "12\n";
  draw([](int x, int y) { return (x * x + y * y) <= 400; });
}

void solution_13() {
  std::cout << "13\n";
  draw([](int x, int y) {
    int y_ = N - 1 - y;
    return (x < y_ + 5) && (x > y_ - 5);
  });
}

void solution_14() {
  std::cout << "14\n";
  draw([](int x, int y) { return x * y <= 100; });
}

void solution_15() {
  std::cout << "15\n";
  draw([](int x, int y) {
    return (x < y - 9) && (x > y - 21) || (y < x - 9) && (y > x - 21);
  });
}

int main() {
  solution_01();
  solution_02();
  solution_03();
  solution_04();
  solution_05();
  solution_06();
  solution_07();
  solution_08();
  solution_09();
  solution_10();
  solution_11();
  solution_12();
  solution_13();
  solution_14();
  solution_15();

  return 0;
}
