#include "algebraic_test.h"
#include "gcd/gcd.h"
#include "utils.h"

using namespace std::string_literals;
using namespace std::string_view_literals;

template <typename T>
void euclidean_sub_test(T a, T b, T expected, int test_index) {
  Timer t;
  auto actual = gcd::euclidean_sub(a, b);
  show_result(actual, expected, test_index, t.duration_ns(), "euclidean_sub"sv);
}

template <typename T>
void euclidean_div_test(T a, T b, T expected, int test_index) {
  Timer t;
  auto actual = gcd::euclidean_div(a, b);
  show_result(actual, expected, test_index, t.duration_ns(), "euclidean_div"sv);
}

template <typename T>
void binary_stein_test(T a, T b, T expected, int test_index) {
  Timer t;
  auto actual = gcd::binary_stein(a, b);
  show_result(actual, expected, test_index, t.duration_ns(), " binary_stein"sv);
}

void gcd_test() {
  std::cout << "--- gcd tests ---"sv << std::endl;

  for (int i = 0;; ++i) {
    auto [ipath, opath] = get_file_paths("gcd"s, i);
    auto in = get_file_content2<long, long>(std::move(ipath));
    auto out = get_file_content1<long>(std::move(opath));

    if (!in || !out) {
      break;
    }

    auto [a, b] = in.value();
    auto expected = out.value();

    euclidean_sub_test(a, b, expected, i);
    euclidean_div_test(a, b, expected, i);
    binary_stein_test(a, b, expected, i);
  }

  std::cout << std::endl;
}