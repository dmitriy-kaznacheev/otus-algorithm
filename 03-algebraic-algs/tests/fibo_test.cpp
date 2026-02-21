#include "algebraic_test.h"
#include "fibo/fibo.h"
#include "utils.h"

template <typename V, typename R>
void fib_recu_test(V n, R expected, int test_index) {
  Timer t;
  auto actual = fibo::fib_recu(n);
  show_result(actual, expected, test_index, t.duration_ns(),
              "      recursion"sv);
}

template <typename V, typename R>
void fib_iter_test(V n, R expected, int test_index) {
  Timer t;
  auto actual = fibo::fib_iter(n);
  show_result(actual, expected, test_index, t.duration_ns(),
              "      iterative"sv);
}

template <typename V, typename R>
void fib_gold_test(V n, R expected, int test_index) {
  Timer t;
  auto actual = fibo::fib_gold(n);
  show_result(actual, expected, test_index, t.duration_ns(),
              "   golden_ratio"sv);
}

template <typename V, typename R>
void fib_mtrx_test(V n, R expected, int test_index) {
  Timer t;
  auto actual = fibo::fib_mtrx(n);
  show_result(actual, expected, test_index, t.duration_ns(),
              "matrix_multiply"sv);
}

void fibo_test() {
  std::cout << "--- fibonacci tests ---"sv << std::endl;

  using ulong = unsigned long;
  for (int i = 0;; ++i) {
    auto [ipath, opath] = get_file_paths("fibo"s, i);
    auto in = get_file_content1<unsigned>(std::move(ipath));
    auto out = get_file_content1<ulong>(std::move(opath));

    if (!in || !out) {
      break;
    }

    auto n = in.value();
    auto expected = out.value();

    fib_recu_test(n, expected, i);
    fib_iter_test(n, expected, i);
    fib_gold_test(n, expected, i);
    fib_mtrx_test(n, expected, i);
  }

  std::cout << std::endl;
}