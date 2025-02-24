// Copyright (c) 2025 TAS
// All rights reserved

#include "module/parser/include/parser.hpp"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <regex>

#include "module/decoder/include/decoder.hpp"
#include "module/instruction/include/instruction.hpp"
#include "module/parser/include/parser_exception.hpp"

const uint16_t kInstructionsInitialAddress = 0x0000;

std::vector<std::string> tas::parser::ReadFileToVector(std::ifstream &input_file, std::string const& file_name) {
  std::vector<std::string> file_contents;
  
  uint32_t file_line_number = 1;

  std::string file_line;
  while (std::getline(input_file, file_line)) {
    std::string file_line_str = file_name + ":" + std::to_string(file_line_number++);
    file_line.insert(0, file_line_str + " ");
    file_contents.push_back(file_line);
  }

  return file_contents;
}

void tas::parser::PreProcessFile(std::vector<std::string>& file_contents) {
  std::map<std::string, std::string> definitions;

  for(int i = 0; i < file_contents.size(); i++) {
    auto &file_content_line = file_contents.at(i);

    tas::instruction::CleanInstruction(file_content_line);

    const auto index = file_content_line.find(' ');
    const auto file_and_line_number = file_content_line.substr(0, index);
    const auto file_line = file_content_line.substr(index + 1);

    if((file_content_line.size() == file_and_line_number.size())) {
      file_content_line.clear();
      continue;
    }
    else if(file_line.at(0) != '\%') {
      continue;
    }

    std::vector<std::string> line_elements;

    tas::instruction::SplitInstruction(file_line, line_elements);

    file_content_line.clear();

    if(line_elements.at(0) == "\%define") {
      definitions[line_elements.at(1)] = line_elements.at(2);
    }
    else if(line_elements.at(0) == "\%include") {
        std::ifstream include_file(line_elements.at(1));
        if (!include_file.is_open()) {
          throw ParserException("File '" + line_elements.at(1) + "' doesn't exist", file_and_line_number); 
        }
        auto include_file_contents = ReadFileToVector(include_file, line_elements.at(1));
        
        
        file_contents.insert(file_contents.begin() + i, include_file_contents.begin(), include_file_contents.end());
    } 
  }

  std::for_each(definitions.begin(), definitions.end(), [&](auto const& def){
    std::for_each(file_contents.begin(), file_contents.end(), [&](auto& e) {
      const std::regex word_regex("\\b" + def.first + "\\b");
      e = std::regex_replace(e, word_regex, def.second);
    });
  });

  for(int i = 0; i < file_contents.size(); i++) {
    if(file_contents.at(i).empty()) {
      file_contents.erase(file_contents.begin() + i--);
    }
  }
}

void tas::parser::ParseFileLabels(std::vector<std::string>& file_contents, std::map<int, std::vector<std::string>> &instructions, std::map<uint16_t, std::string> &labels) {
  uint16_t address = kInstructionsInitialAddress;

  for (int line = 0; line < file_contents.size(); line++) {
    auto& file_content_line = file_contents.at(line);

    const auto index = file_content_line.find(' ');
    const auto file_and_line_number = file_content_line.substr(0, index);
    auto instruction = file_content_line.substr(index + 1);

    try {
      if (instruction.empty()) {
        continue;
      }
      else {
        size_t pos = instruction.find(':');

        if (pos != std::string::npos) {
          std::string line_label = instruction.substr(0, pos);

          size_t instruction_start = pos + 1;
          while (instruction_start < instruction.size() && std::isspace(static_cast<unsigned char>(instruction[instruction_start]))) {
              instruction_start++;
          }

          auto it = std::find_if(labels.cbegin(), labels.cend(), [&](auto const &label) {
            return label.second == line_label;
          });

          if(it != labels.cend()) {
            throw std::invalid_argument("Duplicated label '" + it->second + "'");
          }
          
          labels[address] = line_label;

          if(instruction_start >= instruction.size()) {
            continue;
          }
          else {
            size_t label_pos = file_content_line.find(line_label);
            file_content_line.erase(label_pos, instruction_start);
          }
        }
      }

      instruction = file_content_line.substr(index + 1);

      std::vector<std::string> instruction_elements;
      instruction_elements.push_back(std::to_string(address));
      tas::instruction::SplitInstruction(instruction, instruction_elements);
      instructions[line + 1] = instruction_elements;

      address += 2;
    } catch (std::exception &e) {
      throw ParserException(e.what(), file_and_line_number);
    }
  }
}

void tas::parser::ParseInstructions(std::ofstream &output_file, std::vector<std::string>& file_contents, std::map<int, std::vector<std::string>> &instructions, std::map<uint16_t, std::string> &labels, bool print_output) {
  std::vector<uint16_t> instructions_binaries;
  uint16_t current_line = 0;
  std::for_each(instructions.begin(), instructions.end(), [&](auto const &instruction) {
    const auto index = file_contents.at(instruction.first - 1).find(' ');
    const auto file_and_line_number = file_contents.at(instruction.first - 1).substr(0, index);
    const auto file_line = file_contents.at(instruction.first - 1).substr(index + 1);
    
    try {
      uint16_t instruction_binary = tas::decoder::DecodeInstruction(instruction.second, labels);
      instructions_binaries.push_back(instruction_binary);
      output_file << std::setfill('0') << std::setw(4) << std::hex << instruction_binary << "\n";
      
      if(print_output) {
        const uint16_t address = std::stoi(instruction.second.front());
        std::printf("%04d: %-30s : 0x%04X: 0x%04X\n", (address - kInstructionsInitialAddress), file_line.c_str(), address, instruction_binary);
      }
    } catch (std::exception &e) {
      throw ParserException(e.what(), file_and_line_number);
    }
  });
}
