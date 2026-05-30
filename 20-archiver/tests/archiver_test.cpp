#include <gtest/gtest.h>

#include <archiver/algorithm_rle.h>
#include <archiver/archiver.h>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;
using namespace std::string_literals;

namespace utils {
fs::path create_temp_file(std::string_view content) {
  auto path_template = fs::temp_directory_path() / "test_archiver_XXXXXX"s;

  std::string mutable_path = path_template.string();
  int fd = mkstemp(mutable_path.data());
  if (fd == -1) {
    throw std::runtime_error("mkstemp failed");
  }

  const char *data = content.data();
  auto remaining = content.size();
  while (remaining > 0) {
    auto written = write(fd, data, remaining);
    if (written == -1) {
      close(fd);
      throw std::runtime_error("write failed");
    }
    remaining -= written;
    data += written;
  }

  close(fd);
  return fs::path(mutable_path);
}

std::string read_conent(const fs::path &file_path) {
  std::ifstream in(file_path, std::ios::binary);
  return std::string(std::istreambuf_iterator<char>{in},
                     std::istreambuf_iterator<char>{});
}
} // namespace utils

TEST(archiver, small_file) {
  auto alg = std::make_unique<compression::AlgorithmRle>();
  auto archiver = compression::Archiver{std::move(alg)};

  auto content = "AAABBBBBCCCCCCCCDDDDDDDDDEEEEEEEEEEEEEEEE"s;
  auto original = utils::create_temp_file(content);
  auto archive = fs::temp_directory_path() / "test_archive.arch"s;
  auto restored = fs::temp_directory_path() / "test_restored.txt"s;

  ASSERT_TRUE(archiver.compress(original.string(), archive.string()));
  ASSERT_TRUE(archiver.decompress(archive.string(), restored.string()));

  auto result = utils::read_conent(restored);
  EXPECT_EQ(content, result);

  fs::remove(original);
  fs::remove(archive);
  fs::remove(restored);
}

TEST(archiver, empty_file) {
  auto alg = std::make_unique<compression::AlgorithmRle>();
  auto archiver = compression::Archiver{std::move(alg)};

  auto content = ""s;
  auto original = utils::create_temp_file(content);
  auto archive = fs::temp_directory_path() / "test_archive.arch"s;
  auto restored = fs::temp_directory_path() / "test_restored.txt"s;

  ASSERT_TRUE(archiver.compress(original.string(), archive.string()));
  ASSERT_TRUE(archiver.decompress(archive.string(), restored.string()));

  auto result = utils::read_conent(restored);
  EXPECT_TRUE(result.empty());

  fs::remove(original);
  fs::remove(archive);
  fs::remove(restored);
}

TEST(archiver, big_file) {
  auto alg = std::make_unique<compression::AlgorithmRle>();
  auto archiver = compression::Archiver{std::move(alg)};

  auto content = std::string(1000, '\xFF');
  auto original = utils::create_temp_file(content);
  auto archive = fs::temp_directory_path() / "test_archive.arch"s;
  auto restored = fs::temp_directory_path() / "test_restored.txt"s;

  ASSERT_TRUE(archiver.compress(original.string(), archive.string()));
  ASSERT_TRUE(archiver.decompress(archive.string(), restored.string()));

  auto result = utils::read_conent(restored);
  EXPECT_EQ(content, result);

  fs::remove(original);
  fs::remove(archive);
  fs::remove(restored);
}

TEST(archiver, missing_file) {
  auto alg = std::make_unique<compression::AlgorithmRle>();
  auto archiver = compression::Archiver{std::move(alg)};

  EXPECT_FALSE(archiver.compress("nonexistent.txt"s, "test_archive.arch"s));
  EXPECT_FALSE(archiver.decompress("nonexistent.arch"s, "test_restored.txt"s));
}

namespace compression {
class MockAlgorithm : public Algorithm {
public:
  ByteBuffer encode(const ByteBuffer &data) const override {
    // "сжатие": добавляет в начало байт 0xFF
    ByteBuffer result;
    result.push_back(0xFF);
    result.insert(result.end(), data.begin(), data.end());
    return result;
  }

  ByteBuffer decode(const ByteBuffer &encoded) const override {
    if (encoded.empty() || (encoded[0] != 0xFF)) {
      throw std::runtime_error("MockAlgorithm: invalid format");
    }
    return ByteBuffer(encoded.begin() + 1, encoded.end());
  }
};
} // namespace compression

TEST(archiver, mock_algorithm) {
  auto mock = std::make_unique<compression::MockAlgorithm>();
  auto archiver = compression::Archiver{std::move(mock)};

  auto content = "Hello, world!"s;
  auto original = utils::create_temp_file(content);
  auto archive = fs::temp_directory_path() / "test_archive.arch"s;
  auto restored = fs::temp_directory_path() / "test_restored.txt"s;

  ASSERT_TRUE(archiver.compress(original.string(), archive.string()));
  ASSERT_TRUE(archiver.decompress(archive.string(), restored.string()));

  auto result = utils::read_conent(restored);
  EXPECT_EQ(content, result);

  fs::remove(original);
  fs::remove(archive);
  fs::remove(restored);
}
