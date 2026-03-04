#include "utils.h"

#include <filesystem>
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

void test_external_sort() {
  std::cout << "--- external_sort ---"sv << std::endl;

  using value_type = int;
  const int max_value = 9;
  const int chunk_size = 1'000;

  const std::string ifpath = get_file_path("gen_file.in"s);
  const std::string ofpath = get_file_path("gen_file.out"s);

  int index = 0;
  for (size_t i = 100; i < 100'000'000; i *= 10) {
    file_generator<value_type>(i, max_value, ifpath);

    size_t duration{};
    {
      Timer t;
      sort::external::sort<value_type>(ifpath, ofpath, chunk_size);
      duration = t.duration_ns();
    }

    bool is_ok = check_sorted<value_type>(ofpath);
    std::cout << (is_ok ? "[ + ]"sv : "[ - ]"sv) << " test_"sv << (++index)
              << ": "sv << std::setw(8) << i << " "sv << duration << " us"sv
              << std::endl;

    std::filesystem::remove(ifpath);
    std::filesystem::remove(ofpath);
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

  test_external_sort();

  return 0;
}
