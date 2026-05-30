#pragma once

#include <archiver/algorithm.h>

namespace compression {

class AlgorithmRle final : public Algorithm {
public:
  ByteBuffer encode(const ByteBuffer &data) const override;
  ByteBuffer decode(const ByteBuffer &encoded) const override;
};

} // namespace compression
