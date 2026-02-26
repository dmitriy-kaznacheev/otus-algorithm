#include "utils.h"

#include <functional>
#include <heap_sort/heap_sort.h>
#include <heap_sort/selection_sort.h>

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

  test(heap::sort<It<int>>, "heap"sv, "random"sv);
  test(heap::sort<It<int>>, "heap"sv, "digits"sv);
  test(heap::sort<It<int>>, "heap"sv, "sorted"sv);
  test(heap::sort<It<int>>, "heap"sv, "revers"sv);

  test(selection::sort<It<int>>, "selection"sv, "random"sv);
  test(selection::sort<It<int>>, "selection"sv, "digits"sv);
  test(selection::sort<It<int>>, "selection"sv, "sorted"sv);
  test(selection::sort<It<int>>, "selection"sv, "revers"sv);

  return 0;
}
