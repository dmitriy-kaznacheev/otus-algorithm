#include "utils.h"

#include <functional>
#include <simple_sort/bubble_sort.h>
#include <simple_sort/insertion_sort.h>
#include <simple_sort/shell_sort.h>

template <typename T> using It = std::vector<T>::iterator;

template <typename Callable>
void test(Callable sort, std::string_view test_name,
          std::string_view test_set) {
  std::cout << "--- "sv << test_name << " ["sv << test_set << "] ---"sv
            << std::endl;

  for (int i = 0;; ++i) {
    auto [ipath, opath] = get_file_paths(std::string(test_set), i);

    auto in_vec = read_vector<int>(std::move(ipath));
    auto out_vec = read_vector<int>(std::move(opath), in_vec.size());
    if (in_vec.empty() || out_vec.empty()) {
      break;
    }

    {
      Timer t;
      sort(std::begin(in_vec), std::end(in_vec));
      show_result(std::move(in_vec), std::move(out_vec), i, t.duration_ns());
    }
  }

  std::cout << std::endl;
}

int main() {
  using namespace sort;

  test(bubble::sort<It<int>>, "bubble"sv, "random"sv);
  test(bubble::sort<It<int>>, "bubble"sv, "digits"sv);
  test(bubble::sort<It<int>>, "bubble"sv, "sorted"sv);
  test(bubble::sort<It<int>>, "bubble"sv, "revers"sv);

  test(insertion::sort<It<int>>, "insertion"sv, "random"sv);
  test(insertion::sort<It<int>>, "insertion"sv, "digits"sv);
  test(insertion::sort<It<int>>, "insertion"sv, "sorted"sv);
  test(insertion::sort<It<int>>, "insertion"sv, "revers"sv);

  test(shell::sort<It<int>>, "shell"sv, "random"sv);
  test(shell::sort<It<int>>, "shell"sv, "digits"sv);
  test(shell::sort<It<int>>, "shell"sv, "sorted"sv);
  test(shell::sort<It<int>>, "shell"sv, "revers"sv);

  return 0;
}
