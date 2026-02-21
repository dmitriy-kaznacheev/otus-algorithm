#include "algebraic_test.h"
#include "power/power.h"
#include "utils.h"

template <typename V, typename P>
void itr_pow_test(V base, P exp, V expected, int test_index) {
  Timer t;
  auto actual = power::itr_pow(base, exp);
  show_result(actual, expected, test_index, t.duration_ns(), "itr_pow"sv);
}

template <typename V, typename P>
void two_pow_test(V base, P exp, V expected, int test_index) {
  Timer t;
  auto actual = power::two_pow(base, exp);
  show_result(actual, expected, test_index, t.duration_ns(), "two_pow"sv);
}

template <typename V, typename P>
void bin_pow_test(V base, P exp, V expected, int test_index) {
  Timer t;
  auto actual = power::bin_pow(base, exp);
  show_result(actual, expected, test_index, t.duration_ns(), "bin_pow"sv);
}

void power_test() {
  std::cout << "--- power tests ---"sv << std::endl;

  for (int i = 0;; ++i) {
    auto [ipath, opath] = get_file_paths("power"s, i);
    auto in = get_file_content2<double, unsigned long>(std::move(ipath));
    auto out = get_file_content1<double>(std::move(opath));

    if (!in || !out) {
      break;
    }

    auto [base, exp] = in.value();
    auto expected = out.value();

    itr_pow_test(base, exp, expected, i);
    two_pow_test(base, exp, expected, i);
    bin_pow_test(base, exp, expected, i);
  }

  std::cout << std::endl;
}