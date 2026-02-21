#include "basic_ds_test.h"
#include "sparse_array/sparse_array.h"
#include "utils.h"

namespace basic_ds_test {

using namespace basic_ds;

void sparse_array_test() {
  std::cout << "--- sparse  array tests ---"sv << std::endl;

  SparceArray<int> sa;

  {
    std::cout << " in: "sv;
    for (int i = 0, v = 5; i < 10; i += 3, v += 5) {
      std::cout << i << ":"sv << v << " "sv;
      sa.add(v, i);
    }
    std::cout << std::endl;
  }

  {
    std::cout << "out: "sv;
    for (int i = 0; i != 15; ++i) {
      std::cout << i << ":"sv;

      if (sa[i].has_value()) {
        std::cout << sa[i].value() << " "sv;
      } else {
        std::cout << "x"sv << " "sv;
      }
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
}

} // namespace basic_ds_test
