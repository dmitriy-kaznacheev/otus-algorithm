#include "utils.h"

#include <linear_sort/bucket_sort.h>
#include <linear_sort/counting_sort.h>
#include <linear_sort/radix_sort.h>

template <typename T> using It = std::vector<T>::iterator;

template <typename T, typename Callable>
void test(Callable sort, std::string file_path, std::string_view test_name) {
  auto data = read_file<T>(std::move(file_path));

  size_t duration{};
  {
    Timer t;
    sort(data.begin(), data.end());
    duration = t.duration();
  }

  bool is_sorted = std::is_sorted(data.begin(), data.end());

  // clang-format off
  std::cout << (is_sorted ? "[ + ]"sv : "[ - ]"sv) 
            << std::setw(7) << test_name << ": "sv 
            << data.size() << " "sv << duration << " sec."sv
            << std::endl;
  // clang-format on
}

int main() {
  const auto file_path{"./data.bin"s};
  const size_t size{100'000'000};

  using value_type = unsigned short;
  using it_type = It<value_type>;

  generate_file<value_type>(size, file_path);
  {
    using namespace sort;
    test<value_type>(bucket::sort<it_type>, file_path, "bucket"sv);
    test<value_type>(counting::sort<it_type>, file_path, "count"sv);
    test<value_type>(radix::sort<it_type>, file_path, "radix"sv);
  }
  remove_file(file_path);

  return 0;
}