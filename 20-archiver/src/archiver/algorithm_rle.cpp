#include <archiver/algorithm_rle.h>
#include <archiver/archiver.h>
#include <stdexcept>

namespace compression {

ByteBuffer AlgorithmRle::encode(const ByteBuffer &data) const {
  ByteBuffer encoded;
  encoded.reserve(data.size());

  size_t i = 0;
  while (i < data.size()) {
    Byte current = data[i];
    size_t count = 1;
    while (((i + count) < data.size()) && (data[i + count] == current) &&
           (count < 255)) {
      ++count;
    }
    encoded.push_back(static_cast<Byte>(count));
    encoded.push_back(current);
    i += count;
  }

  return encoded;
}

ByteBuffer AlgorithmRle::decode(const ByteBuffer &encoded) const {
  if (encoded.size() % 2 != 0) {
    throw std::runtime_error("AlgorithmRle::decode: odd number of bytes");
  }

  ByteBuffer decoded;
  decoded.reserve(encoded.size());

  for (size_t i = 0; i < encoded.size(); i += 2) {
    Byte count = encoded[i];
    Byte byte = encoded[i + 1];

    if (count == 0) {
      throw std::runtime_error("AlgorithmRle::decode: zero count");
    }

    while (count--) {
      decoded.push_back(byte);
    }
  }

  return decoded;
}

} // namespace compression
