// Copyright (c) 2025 TAS
// All rights reserved

#pragma once

#include <cstdint>
#include <fstream>
#include <map>
#include <string>
#include <vector>

namespace tas {
namespace parser {

std::vector<std::string> ReadFileToVector(std::ifstream &input_file);

void PreParseFileLabels(std::vector<std::string>& file_contents, std::map<int, std::vector<std::string>>& instructions, std::map<uint16_t, std::string>& labels);

void ParseInstructions(std::ofstream& output_file, std::vector<std::string>& file_contents, std::map<int, std::vector<std::string>>& instructions, std::map<uint16_t, std::string>& labels, bool print_output = true);

}  // namespace parser
}  // namespace tas
