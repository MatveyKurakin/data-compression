#pragma once

#include <string>

namespace data_compression {

void encoding(const std::string& inputFileName, const std::string& outputFileName);
void decoding(const std::string& inputFileName, const std::string& outputFileName);
bool cmp_file(const std::string& inputFileName_1, const std::string& inputFileName_2);
std::string gen_output_file_name(const std::string& inputFileName, const std::string& ext);

}  // namespace data_compression