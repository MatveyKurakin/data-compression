#include <iostream>

#include "data_compression.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Incorrect number of arguments\n"
              << "./huffman -c <input_file> [output_file]\n"
              << "./huffman -d <input_file> [output_file]\n";
    return 1;
  }

  std::string mode = argv[1];
  if (mode != "-c" && mode != "-d") {
    std::cerr << "Unknown mode\n"
              << "./huffman -c <input_file> [output_file]\n"
              << "./huffman -d <input_file> [output_file]\n";
    return 1;
  }

  std::string inputFileName = argv[2];
  std::string outputFileName;
  if (argc > 3) {
    outputFileName = argv[3];
  } else {
    if (mode == "-c")
      outputFileName =
          data_compression::gen_output_file_name(inputFileName, ".huff");
    else
      outputFileName =
          data_compression::gen_output_file_name(inputFileName, ".txt");
  }

  if (mode == "-c")
    data_compression::encoding(inputFileName, outputFileName);
  else if (mode == "-d")
    data_compression::decoding(inputFileName, outputFileName);

  std::cout << "Completed\n";
  return 0;
}
