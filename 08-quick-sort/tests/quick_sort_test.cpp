#include "utils.h"

#include <functional>
#include <quick_sort/external_sort.h>
#include <quick_sort/merge_sort.h>
#include <quick_sort/quick_sort.h>

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

  test(quick::sort<It<int>>, "quick"sv, "random"sv);
  test(quick::sort<It<int>>, "quick"sv, "digits"sv);
  test(quick::sort<It<int>>, "quick"sv, "sorted"sv);
  test(quick::sort<It<int>>, "quick"sv, "revers"sv);

  test(merge::sort<It<int>>, "merge"sv, "random"sv);
  test(merge::sort<It<int>>, "merge"sv, "digits"sv);
  test(merge::sort<It<int>>, "merge"sv, "sorted"sv);
  test(merge::sort<It<int>>, "merge"sv, "revers"sv);

  return 0;
}
