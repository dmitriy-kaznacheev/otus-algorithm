#include <gtest/gtest.h>

#include <archiver/algorithm_rle.h>

TEST(algorithm_rle, empty) {
  compression::AlgorithmRle alg;
  compression::ByteBuffer data{};

  auto encoded = alg.encode(data);
  EXPECT_TRUE(encoded.empty());

  auto decoded = alg.decode(encoded);
  EXPECT_TRUE(decoded.empty());
}

TEST(algorithm_rle, single_byte) {
  compression::AlgorithmRle alg;
  compression::ByteBuffer data{0x42};

  auto encoded = alg.encode(data);
  ASSERT_EQ(encoded.size(), 2);
  EXPECT_EQ(encoded[0], 1);
  EXPECT_EQ(encoded[1], 0x42);

  auto decoded = alg.decode(encoded);
  EXPECT_EQ(decoded, data);
}

TEST(algorithm_rle, length_less_255) {
  compression::AlgorithmRle alg;
  compression::ByteBuffer data(100, 0x55);

  auto encoded = alg.encode(data);
  ASSERT_EQ(encoded.size(), 2);
  EXPECT_EQ(encoded[0], 100);
  EXPECT_EQ(encoded[1], 0x55);

  auto decoded = alg.decode(encoded);
  EXPECT_EQ(decoded, data);
}

TEST(algorithm_rle, length_equal_255) {
  compression::AlgorithmRle alg;
  compression::ByteBuffer data(255, 0x77);

  auto encoded = alg.encode(data);
  ASSERT_EQ(encoded.size(), 2);
  EXPECT_EQ(encoded[0], 255);
  EXPECT_EQ(encoded[1], 0x77);

  auto decoded = alg.decode(encoded);
  EXPECT_EQ(decoded, data);
}

TEST(algorithm_rle, length_longer_255) {
  compression::AlgorithmRle alg;
  compression::ByteBuffer data(300, 0x88);

  auto encoded = alg.encode(data);
  ASSERT_EQ(encoded.size(), 4);
  EXPECT_EQ(encoded[0], 255);
  EXPECT_EQ(encoded[1], 0x88);
  EXPECT_EQ(encoded[2], 45);
  EXPECT_EQ(encoded[3], 0x88);

  auto decoded = alg.decode(encoded);
  EXPECT_EQ(decoded, data);
}

TEST(algorithm_rle, mixed) {
  compression::AlgorithmRle alg;
  compression::ByteBuffer data{0x01, 0x01, 0x02, 0x02, 0x02, 0x03};

  auto encoded = alg.encode(data);
  ASSERT_EQ(encoded.size(), 6);
  EXPECT_EQ(encoded[0], 2);
  EXPECT_EQ(encoded[1], 0x01);
  EXPECT_EQ(encoded[2], 3);
  EXPECT_EQ(encoded[3], 0x02);
  EXPECT_EQ(encoded[4], 1);
  EXPECT_EQ(encoded[5], 0x03);

  auto decoded = alg.decode(encoded);
  EXPECT_EQ(decoded, data);
}

TEST(algorithm_rle, invalid_odd_length) {
  compression::AlgorithmRle alg;
  compression::ByteBuffer invalid{1, 0xAA, 2};

  EXPECT_THROW(alg.decode(invalid), std::runtime_error);
}

TEST(algorithm_rle, invalid_zero_count) {
  compression::AlgorithmRle alg;
  compression::ByteBuffer invalid{0, 0xAA, 1, 0xBB};

  EXPECT_THROW(alg.decode(invalid), std::runtime_error);
}
