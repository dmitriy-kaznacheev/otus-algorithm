#include <cmath>
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

void solution_16() {
  std::cout << "16\n";
  draw([](int x, int y) {
    int y_ = N - 1 - y;
    int offset = 10;
    return (x > y - offset) && (y > x - offset) && (x > y_ - offset) &&
           (x < y_ + offset);
  });
}

void solution_17() {
  std::cout << "17\n";
  draw([](int x, int y) { return y/8. - 2.  > std::sin(x / 3.); });
}

void solution_18() {
  std::cout << "18\n";
  draw([](int x, int y) { return (x < 2 || y < 2) && (x + y > 0); });
}

void solution_19() {
  std::cout << "19\n";
  draw([](int x, int y) { return ((x == 0) || (y == 0) || (x == N-1) || (y == N-1)); });
}

void solution_20() {
  std::cout << "20\n";
  draw([](int x, int y) { return (x + y) % 2 == 0; });
}

void solution_21() {
  std::cout << "21\n";
  draw([](int x, int y) { return (x % (y + 1) == 0); });
}

void solution_22() {
  std::cout << "22\n";
  draw([](int x, int y) { return (x + y) % 3 == 0; });
}

void solution_23() {
  std::cout << "23\n";
  draw([](int x, int y) { return (x % 2 == 0) && (y % 3 == 0); });
}

void solution_24() {
  std::cout << "24\n";
  draw([](int x, int y) { 
    int y_ = N -1 - y;
    return (x == y) || (x == y_); });
}

void solution_25() {
  std::cout << "25\n";
  draw([](int x, int y) { return (x % 6 == 0) || (y % 6 == 0); });
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
  solution_16();
  solution_17();
  solution_18();
  solution_19();
  solution_20();
  solution_21();
  solution_22();
  solution_23();
  solution_24();
  solution_25();

  return 0;
}
