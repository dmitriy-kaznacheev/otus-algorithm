#pragma once

#include <archiver/algorithm.h>
#include <memory>
#include <string>

namespace compression {

class Archiver {
public:
  explicit Archiver(std::unique_ptr<Algorithm> algorithm);

  bool compress(const std::string &ipath, const std::string &opath) const;
  bool decompress(const std::string &ipath, const std::string &opath) const;

private:
  std::unique_ptr<Algorithm> algorithm_;
};

} // namespace compression
