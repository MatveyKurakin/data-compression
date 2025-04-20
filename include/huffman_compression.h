#pragma once

#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

namespace huffman_comprassion {

class HuffmanTree {
 protected:
  struct Node {
    char data_;
    std::shared_ptr<Node> left_;
    std::shared_ptr<Node> right_;
    Node(char data) : data_(data), left_(nullptr), right_(nullptr) {}
  };
  std::shared_ptr<Node> root_;

 public:
  void build_tree(std::unordered_map<char, std::size_t>& freqs);
  void build_tree(const std::string& str_tree);
};

class HuffmanEncoder : HuffmanTree {
  std::unordered_map<char, std::size_t> count_freq(std::ifstream& in);
  std::unordered_map<char, std::string> generate_codes();
  std::stringstream serialize_tree();
  void encode_data(std::ifstream& in, std::ofstream& out, std::unordered_map<char, std::string>& codes);

 public:
  void encode(std::ifstream& in, std::ofstream& out);
};

class HuffmanDecoder : HuffmanTree {
  std::string serialize_tree(std::ifstream& in);
  void decode_data(std::ifstream& in, std::ofstream& out, char pos);

 public:
  void decode(std::ifstream& in, std::ofstream& out);
};

}  // namespace huffman_comprassion
