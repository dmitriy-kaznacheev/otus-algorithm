#include <archiver/archiver.h>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

namespace compression {

using ByteIter = std::istreambuf_iterator<char>;

Archiver::Archiver(std::unique_ptr<Algorithm> algorithm)
    : algorithm_(std::move(algorithm)) {}

bool Archiver::compress(const std::string &ipath,
                        const std::string &opath) const {
  std::ifstream in(ipath, std::ios::binary);
  if (!in) {
    std::cerr << "Archiver: cannot open input file " << ipath << std::endl;
    return false;
  }

  ByteBuffer data(ByteIter{in}, ByteIter{});
  in.close();

  ByteBuffer compressed = algorithm_->encode(data);

  std::ofstream out(opath, std::ios::binary);
  if (!out) {
    std::cerr << "Archiver: cannot create output file " << opath << std::endl;
    return false;
  }
  out.write(reinterpret_cast<const char *>(compressed.data()),
            compressed.size());
  out.close();

  std::cout << "Compressed " << data.size() << " -> " << compressed.size()
            << " bytes"
            << " (ratio: " << (compressed.size() * 100.0 / data.size()) << "%)"
            << std::endl;
  return true;
}

bool Archiver::decompress(const std::string &ipath,
                          const std::string &opath) const {
  std::ifstream in(ipath, std::ios::binary);
  if (!in) {
    std::cerr << "Archiver: cannot open input file " << ipath << std::endl;
    return false;
  }

  ByteBuffer compressed(ByteIter{in}, ByteIter{});
  in.close();

  try {
    ByteBuffer decompressed = algorithm_->decode(compressed);
    std::ofstream out(opath, std::ios::binary);
    if (!out) {
      std::cerr << "Archiver: cannot create output file " << opath << std::endl;
      return false;
    }
    out.write(reinterpret_cast<const char *>(decompressed.data()),
              decompressed.size());
    out.close();

    std::cout << "Decompressed " << compressed.size() << " -> "
              << decompressed.size() << " bytes" << std::endl;
    return true;
  } catch (const std::exception &e) {
    std::cerr << "Archiver: decompression error - " << e.what() << std::endl;
    return false;
  }
}

} // namespace compression
