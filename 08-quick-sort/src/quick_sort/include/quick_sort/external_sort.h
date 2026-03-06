#pragma once
#include <quick_sort/merge_sort.h>

#include <filesystem>
#include <fstream>
#include <queue>
#include <sstream>
#include <vector>

namespace sort {
namespace external {

namespace {
using namespace std::string_literals;
using namespace std::string_view_literals;

template <typename T> struct Value {
  T value;
  size_t chunk_number;
  auto operator<=>(const Value &) const = default;
};

std::string chunk_file_name(size_t chunk_number) {
  std::stringstream ss{};
  ss << "chunk_"sv << chunk_number;
  return std::move(ss.str());
}

void remove_chunk_files(size_t chunk_count) {
  for (size_t i = 0; i != chunk_count; ++i) {
    std::filesystem::remove(chunk_file_name(i));
  }
}

template <typename It> void save_chunk(It first, It last, size_t chunk_number) {
  std::ofstream f{chunk_file_name(chunk_number)};
  for (It it = first; it != last; ++it) {
    f << (*it) << "\n";
  }
}

template <typename It> void sort_chunk(It first, It last, size_t chunk_number) {
  merge::sort(first, last);
  save_chunk<It>(first, last, chunk_number);
}
} // namespace

template <typename T>
void sort(std::string ifpath, std::string ofpath, size_t chunk_size) {
  size_t chunk_count{};

  {
    std::vector<T> chunk;
    chunk.reserve(chunk_size);
    std::ifstream f{std::move(ifpath)};
    for (T value; f >> value;) {
      chunk.push_back(std::move(value));
      if (chunk.size() == chunk_size) {
        sort_chunk(std::begin(chunk), std::end(chunk), chunk_count++);
        chunk.clear();
      }
    }
    if (!chunk.empty()) {
      sort_chunk(std::begin(chunk), std::end(chunk), chunk_count++);
    }
  }

  {
    std::priority_queue<Value<T>, std::vector<Value<T>>, std::greater<Value<T>>> pq;
    std::vector<std::ifstream> chunk_files(chunk_count);

    for (size_t i = 0; i != chunk_count; ++i) {
      chunk_files[i].open(chunk_file_name(i));
      if (T value; chunk_files[i] >> value) {
        pq.push({value, i});
      }
    }

    {
      std::ofstream f{std::move(ofpath)};
      while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        f << top.value << "\n";

        if (T value; chunk_files[top.chunk_number] >> value) {
          pq.push({value, top.chunk_number});
        }
      }
    }
  }

  remove_chunk_files(chunk_count);
}

} // namespace external
} // namespace sort
