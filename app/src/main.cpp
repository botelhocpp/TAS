// Copyright (c) 2025 TAS
// All rights reserved

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "module/decoder/include/decoder.hpp"
#include "module/instruction/include/instruction.hpp"
#include "module/parser/include/parser.hpp"
#include "module/parser/include/parser_exception.hpp"

extern "C" {
#include "utils/getopt/include/getopt.h"
}

constexpr int kSucessCode = 0;
constexpr int kTooMuchParametersErrorCode = 1;
constexpr int kNoInputFileErrorCode = 2;
constexpr int kInputFileNotFoundErrorCode = 3;
constexpr int kInvalidInputFileExtensionErrorCode = 4;
constexpr int kInvalidOptionCode = 5;
constexpr int kParsingErrorCode = 6;
constexpr int kMinNumberParameters = 1;
constexpr int kMaxNumberParameters = 4;

int main(int argc, char *argv[]) {
  if (argc > kMaxNumberParameters + 1) {
    std::cerr << "\033[1;37mTAS:\033[0m \033[1;31mfatal error\033[0m: Too much parameters.\nAborting.\n";
    return kTooMuchParametersErrorCode;
  } else if (argc < kMinNumberParameters + 1) {
    std::cerr << "\033[1;37mTAS:\033[0m \033[1;31mfatal error\033[0m: No input file.\nAborting.\n";
    return kNoInputFileErrorCode;
  }

  std::string input_file_name;
  input_file_name = argv[1];

  std::ifstream input_file(input_file_name);
  if (!input_file.is_open()) {
    std::cerr << "\033[1;37mTAS:\033[0m \033[1;31mfatal error\033[0m: " << input_file_name << ": File doesn't exist.\nAborting.\n";
    return kInputFileNotFoundErrorCode;
  }

  if (input_file_name.find(".asm") == input_file_name.npos) {
    std::cerr << "\033[1;37mTAS:\033[0m \033[1;31mfatal error\033[0m: " << input_file_name << ": Invalid extension.\nAborting.\n";
    return kInvalidInputFileExtensionErrorCode;
  }

  bool informed_output_file = false;
  std::string output_file_name;
  bool print_output = false;

  int option;
  while ((option = getopt(argc - 1, argv + 1, "po:")) != -1) {
    switch (option) {
      case 'p':
        print_output = true;
        break;
      case 'o':
        informed_output_file = true;
        output_file_name = optarg;
        break;
      case '?':
        if (optopt == 'o') {
          std::fprintf(stderr, "Option -%c requires an argument.\n", optopt);
        } else if (std::isprint(optopt)) {
          std::fprintf(stderr, "Unknown option `-%c'.\n", optopt);
        } else {
          std::fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
        }
        return kInvalidOptionCode;
      default:
        std::fprintf(stderr, "Usage: %s <input_file> [-o <output_file>] [-p]\n", argv[0]);
        return kInvalidOptionCode;
    }
  }

  if (!informed_output_file) {
    output_file_name = input_file_name;
    output_file_name.erase(output_file_name.find(".asm"));
  }

  std::ofstream output_file(output_file_name);
  try {
    std::vector<std::string> file_contents = tas::parser::ReadFileToVector(input_file);

    std::map<int, std::vector<std::string>> instructions;
    std::map<uint16_t, std::string> labels;
    tas::parser::PreParseFileLabels(file_contents, instructions, labels);

    tas::parser::ParseInstructions(output_file, file_contents, instructions, labels, print_output);
  } catch (tas::parser::ParserException &e) {
    std::cerr << "\033[1;37m" << input_file_name << ":" << e.GetLine() << ":\033[0m \033[1;31merror\033[0m: " << e.what() << ".\nAborting.\n";
    std::remove(output_file_name.c_str());
    return kParsingErrorCode;
  }

  return kSucessCode;
}
