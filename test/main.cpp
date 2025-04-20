#include <string>

#include "data_compression.h"
#include "gtest.h"

std::string data_path = "../../data/";

TEST(HuffmanTest, CompairFile) {
  std::string empty = data_path + "test_CompairFile/empty.txt";
  std::string no_empty = data_path + "test_CompairFile/no_empty.txt";
  EXPECT_TRUE(data_compression::cmp_file(empty, empty));
  EXPECT_FALSE(data_compression::cmp_file(empty, no_empty));
}

TEST(HuffmanTest, GenerateOutputFileName) {
  std::string file_1 = data_path + "test_GenerateOutputFileName/file_1.txt";
  std::string file_1_huf =
      data_path + "test_GenerateOutputFileName/file_1.huff";
  std::string file_2 = data_path + "test_GenerateOutputFileName/file_2";
  std::string file_2_huf =
      data_path + "test_GenerateOutputFileName/file_2.huff";
  EXPECT_EQ(data_compression::gen_output_file_name(file_1, ".huff"),
            file_1_huf);
  EXPECT_EQ(data_compression::gen_output_file_name(file_2, ".huff"),
            file_2_huf);
}

TEST(HuffmanTest, EmptyFileEncodingDecoding) {
  std::string input = data_path + "test_EmptyFileEncodingDecoding/input.txt";
  std::string output = data_path + "test_EmptyFileEncodingDecoding/output.huff";
  std::string decoded =
      data_path + "test_EmptyFileEncodingDecoding/decoded.txt";
  data_compression::encoding(input, output);
  data_compression::decoding(output, decoded);
  EXPECT_TRUE(data_compression::cmp_file(input, decoded));
}

TEST(HuffmanTest, SingleCharEncodingDecoding) {
  std::string input = data_path + "test_SingleCharEncodingDecoding/input.txt";
  std::string output =
      data_path + "test_SingleCharEncodingDecoding/output.huff";
  std::string decoded =
      data_path + "test_SingleCharEncodingDecoding/decoded.txt";
  data_compression::encoding(input, output);
  data_compression::decoding(output, decoded);
  EXPECT_TRUE(data_compression::cmp_file(input, decoded));
}

TEST(HuffmanTest, TextFileEncodingDecoding) {
  std::string input = data_path + "test_TextFileEncodingDecoding/input.txt";
  std::string output = data_path + "test_TextFileEncodingDecoding/output.huff";
  std::string decoded = data_path + "test_TextFileEncodingDecoding/decoded.txt";
  data_compression::encoding(input, output);
  data_compression::decoding(output, decoded);
  EXPECT_TRUE(data_compression::cmp_file(input, decoded));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}