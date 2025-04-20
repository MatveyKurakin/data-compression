#include "data_compression.h"

#include "huffman_compression.h"

void data_compression::encoding(const std::string& inputFileName, const std::string& outputFileName) {
  std::ifstream in(inputFileName, std::ios::binary);
  std::ofstream out(outputFileName, std::ios::binary);

  huffman_comprassion::HuffmanEncoder huffman_encoder;
  huffman_encoder.encode(in, out);

  in.close();
  out.close();
}

void data_compression::decoding(const std::string& inputFileName, const std::string& outputFileName) {
  std::ifstream in(inputFileName, std::ios::binary);
  std::ofstream out(outputFileName, std::ios::binary);

  huffman_comprassion::HuffmanDecoder huffman_decoder;
  huffman_decoder.decode(in, out);

  in.close();
  out.close();
}

bool data_compression::cmp_file(const std::string& inputFileName_1, const std::string& inputFileName_2) {
  std::ifstream in_1(inputFileName_1, std::ios::binary);
  std::ifstream in_2(inputFileName_2, std::ios::binary);
  char c1, c2;
  while (in_1.get(c1)) {
    if (!in_2.get(c2)) {
      in_1.close();
      in_2.close();
      return false;
    }
    if (c1 != c2) {
      in_1.close();
      in_2.close();
      return false;
    }
  }
  if (in_2.get(c2)) {
    in_1.close();
    in_2.close();
    return false;
  }
  in_1.close();
  in_2.close();
  return true;
}

std::string data_compression::gen_output_file_name(const std::string& inputFileName, const std::string& ext) {
  std::size_t ind_slash = inputFileName.find_last_of('/');
  if (ind_slash == std::string::npos) ind_slash = 0;
  std::size_t ind_dot = inputFileName.substr(ind_slash, inputFileName.size()).find_last_of('.');
  std::string outputFileName;
  if (ind_dot != std::string::npos)
    outputFileName = inputFileName.substr(0, ind_slash + ind_dot) + ext;
  else
    outputFileName = inputFileName + ext;
  return outputFileName;
}