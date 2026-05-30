#pragma once

#include <cstdint>
#include <vector>

namespace compression {

using Byte = uint8_t;
using ByteBuffer = std::vector<Byte>;

class Algorithm {
public:
  virtual ~Algorithm() = default;

  virtual ByteBuffer encode(const ByteBuffer &data) const = 0;
  virtual ByteBuffer decode(const ByteBuffer &encoded) const = 0;
};

} // namespace compression
