#include "huffman_compression.h"

#include <queue>
#include <stack>

void huffman_comprassion::HuffmanTree::build_tree(
    std::unordered_map<char, std::size_t> &freqs) {
  using HeapNode = std::pair<std::size_t, std::shared_ptr<Node>>;
  auto cmp = [](const HeapNode &a, const HeapNode &b) {
    return a.first > b.first;
  };
  std::priority_queue<HeapNode, std::vector<HeapNode>, decltype(cmp)> pq{cmp};

  for (auto &f : freqs) {
    HeapNode node = {f.second, std::make_shared<Node>(f.first)};
    pq.push(node);
  }

  if (pq.size() == 1) {
    root_ = std::make_shared<Node>('\0');
    root_->right_ = std::make_shared<Node>('\0');
    root_->left_ = pq.top().second;
    pq.pop();
    return;
  }

  while (pq.size() > 1) {
    HeapNode left = pq.top();
    pq.pop();
    HeapNode right = pq.top();
    pq.pop();
    HeapNode node = {left.first + right.first, std::make_shared<Node>('\0')};
    node.second->left_ = left.second;
    node.second->right_ = right.second;
    pq.push(node);
  }
  root_ = pq.top().second;
}

void huffman_comprassion::HuffmanTree::build_tree(const std::string &str_tree) {
  std::stack<std::shared_ptr<Node>> st;
  root_ = std::make_shared<Node>('\0');
  st.push(root_);
  for (size_t i = 0; i < str_tree.size(); ++i) {
    if (str_tree[i] == '*') {
      std::shared_ptr<Node> current = st.top();
      st.pop();
      current->right_ = std::make_shared<Node>('\0');
      current->left_ = std::make_shared<Node>('\0');
      st.push(current->right_);
      st.push(current->left_);
    } else if (str_tree[i] == 'L') {
      std::shared_ptr<Node> current = st.top();
      st.pop();
      current->data_ = str_tree[++i];
    }
  }
}

std::unordered_map<char, std::size_t>
huffman_comprassion::HuffmanEncoder::count_freq(std::ifstream &in) {
  std::unordered_map<char, std::size_t> freq;

  const size_t BUFFER_SIZE = 4096;
  char inBuffer[BUFFER_SIZE];

  while (in.read(inBuffer, BUFFER_SIZE)) {
    for (std::size_t i = 0; i < BUFFER_SIZE; ++i) {
      ++freq[inBuffer[i]];
    }
  }
  for (std::size_t i = 0; i < in.gcount(); ++i) {
    ++freq[inBuffer[i]];
  }
  in.clear();
  in.seekg(0, std::ios::beg);

  return freq;
}

std::unordered_map<char, std::string>
huffman_comprassion::HuffmanEncoder::generate_codes() {
  std::unordered_map<char, std::string> codes;
  using HeapNode = std::pair<std::shared_ptr<Node>, std::string>;
  std::stack<HeapNode> st;
  st.push({root_, ""});
  while (!st.empty()) {
    HeapNode root = st.top();
    st.pop();
    if (!root.first->left_ && !root.first->right_) {
      codes[root.first->data_] = root.second;
    } else {
      st.push({root.first->right_, root.second + '1'});
      st.push({root.first->left_, root.second + '0'});
    }
  }
  return codes;
}

std::stringstream huffman_comprassion::HuffmanEncoder::serialize_tree() {
  std::stringstream sstr;
  std::stack<std::shared_ptr<Node>> st;
  st.push(root_);
  while (!st.empty()) {
    std::shared_ptr<Node> root = st.top();
    st.pop();
    if (!root->left_ && !root->right_) {
      sstr << 'L' << root->data_;
    } else {
      sstr << "*";
      st.push(root->right_);
      st.push(root->left_);
    }
  }
  return sstr;
}

void huffman_comprassion::HuffmanEncoder::encode_data(
    std::ifstream &in, std::ofstream &out,
    std::unordered_map<char, std::string> &codes) {
  std::size_t pos = 7;
  char out_ch = 0;
  char cur_ch;
  while (in.get(cur_ch)) {
    std::string code = codes.at(cur_ch);
    for (auto &bit : code) {
      if (bit == '1') {
        out_ch = out_ch | (1 << pos);
      }
      if (pos == 0) {
        out.put(out_ch);
        out_ch = 0;
        pos = 8;
      }
      --pos;
    }
  }
  if (pos != 7)
    out.put(out_ch);
  out.seekp(0);
  out.put((pos + 1) % 8);
}

void huffman_comprassion::HuffmanEncoder::encode(std::ifstream &in,
                                                 std::ofstream &out) {
  std::unordered_map<char, std::size_t> freqs = count_freq(in);
  if (freqs.size() == 0)
    return;
  build_tree(freqs);
  std::unordered_map<char, std::string> codes = generate_codes();
  out << 0 << serialize_tree().rdbuf() << "#\n";
  encode_data(in, out, codes);
}

std::string
huffman_comprassion::HuffmanDecoder::serialize_tree(std::ifstream &in) {
  std::string str_tree = "";
  char cur_char;
  while (in.get(cur_char)) {
    if (cur_char == '\n' && str_tree.back() == '#')
      break;
    str_tree += cur_char;
  }
  return str_tree;
}

void huffman_comprassion::HuffmanDecoder::decode_data(std::ifstream &in,
                                                      std::ofstream &out,
                                                      char pos) {
  std::shared_ptr<Node> current = root_;
  const size_t BUFFER_SIZE = 4096;
  char inBuffer[BUFFER_SIZE];
  while (in.read(inBuffer, BUFFER_SIZE)) {
    if (in.eof())
      break;
    for (std::size_t j = 0; j < BUFFER_SIZE; ++j) {
      char in_char = inBuffer[j];
      for (int i = 7; i >= 0; --i) {
        char bit = (in_char >> i) & 1;
        if (bit == 0)
          current = current->left_;
        else
          current = current->right_;

        if (!current->left_ && !current->right_) {
          out.put(current->data_);
          current = root_;
        }
      }
    }
  }
  int last_pos = 0;
  for (std::size_t j = 0; j < in.gcount(); ++j) {
    char in_char = inBuffer[j];
    if (j == in.gcount() - 1)
      last_pos = pos;
    for (int i = 7; i >= last_pos; --i) {
      char bit = (in_char >> i) & 1;
      if (bit == 0)
        current = current->left_;
      else
        current = current->right_;

      if (!current->left_ && !current->right_) {
        out.put(current->data_);
        current = root_;
      }
    }
  }
}

void huffman_comprassion::HuffmanDecoder::decode(std::ifstream &in,
                                                 std::ofstream &out) {
  char pos;
  if (!in.get(pos))
    return;
  if (pos > 7)
    return;
  std::string str_tree = serialize_tree(in);
  build_tree(str_tree);
  decode_data(in, out, pos);
}