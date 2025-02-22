// Copyright (c) 2025 TAS
// All rights reserved

#include "module/instruction/include/instruction.hpp"

#include <algorithm>
#include <sstream>
#include <stdexcept>

#include "module/instruction/include/instructionlist.hpp"
#include "utils/strmanip/include/strmanip.hpp"

constexpr char kCommentSymbol[] = "//";

void tas::instruction::CleanInstruction(std::string& line) {
  strmanip::RemoveComma(line);
  strmanip::RemoveSubstring(line, kCommentSymbol);
  strmanip::RightTrim(line);
  strmanip::LeftTrim(line);
  strmanip::MiddleTrim(line);
}

void tas::instruction::SplitInstruction(const std::string& line, std::vector<std::string>& instruction_elements) {
  std::stringstream line_stream(line);

  std::string token;
  while (std::getline(line_stream, token, ' ')) {
    instruction_elements.push_back(token);
  }

  if (instruction_elements.at(1) == "ldr" || instruction_elements.at(1) == "str") {
    char reg[10];
    char imm[10];
    
    sscanf(instruction_elements.at(3).c_str(), "[%s", reg);

    sscanf(instruction_elements.at(4).c_str(), "#%[^]]", imm);

    instruction_elements.at(3) = reg;
    instruction_elements.at(4) = imm;
  }
}

const tas::instruction::Instruction* tas::instruction::GetInstruction(const std::string& mnemonic) {
  const auto inst_end = std::cend(instructions::kInstructionList);
  const Instruction* instruction = std::find_if(std::cbegin(instructions::kInstructionList), inst_end,
                                                [&](const auto& instruction) {
                                                  return mnemonic == instruction.mnemonic;
                                                });

  if (instruction == inst_end) {
    throw std::invalid_argument("Invalid mnemonic '" + mnemonic + "'");
  }

  return instruction;
}
