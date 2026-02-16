#include "basic_ds_test.h"
#include "priority_queue/priority_queue.h"
#include "utils.h"

namespace basic_ds_test {

using namespace basic_ds;

void priority_queue_test() {
  std::cout << "--- priorit queue tests ---"sv << std::endl;

  PriorityQueue<int> pq;

  {
    std::cout << " in: "sv;
    for (int i = 0, w = 10; i != 10; w += 5, ++i) {
      std::cout << "{"sv << w << ", "sv << i << "} "sv;
      pq.enqueue(w, i);
    }
    std::cout << std::endl;
  }

  {
    std::cout << "out: "sv;
    for (int i = 0; i != 10; ++i) {
      std::cout << pq.dequeue() << " "sv;
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
}

} // namespace basic_ds_test
