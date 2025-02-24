// Copyright (c) 2025 TAS
// All rights reserved

#include "module/decoder/include/decoder.hpp"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <regex>
#include <stdexcept>
#include <unordered_map>

const uint16_t k12bitMask = 0xFFF;
const uint16_t k10bitMask = 0x3FF;
const uint16_t k8bitMask = 0xFF;
const uint16_t k5bitMask = 0x1F;

const uint16_t kRdPosition = 8;
const uint16_t kRmPosition = 5;
const uint16_t kRnPosition = 2;

const std::unordered_map<std::string, uint16_t> kRegisterMap = {
    {"a0", 0},
    {"a1", 1},
    {"t0", 2},
    {"t1", 3},
    {"s0", 4},
    {"s1", 5},
    {"sp", 6},
    {"pc", 7}};

uint16_t tas::decoder::DecodeRegister(const std::string& reg) {
  const auto it = kRegisterMap.find(reg);
  if (it != kRegisterMap.end()) {
    return it->second;
  }

  const std::regex pattern(R"(r(\d+))");
  std::smatch match;
  uint16_t reg_number = 0;
  if (std::regex_match(reg, match, pattern)) {
    reg_number = std::stoi(match[1].str());
    if (reg_number > 7) {
      throw std::invalid_argument("Invalid register '" + reg + "'");
    }
  } else {
    throw std::invalid_argument("Invalid register '" + reg + "'");
  }

  return reg_number;
}

int16_t tas::decoder::DecodeImmediate(const std::string& imm, uint16_t max_val) {
  int16_t imm_val = 0;

  try {
    if (std::strncmp(imm.c_str(), "0x", 2) == 0) {
      imm_val = std::stoi(imm, nullptr, 16);
    } else if (std::strncmp(imm.c_str(), "0o", 2) == 0) {
      imm_val = std::stoi(imm, nullptr, 8);
    } else if (std::strncmp(imm.c_str(), "0b", 2) == 0) {
      imm_val = std::stoi(imm, nullptr, 2);
    } else {
      imm_val = std::stoi(imm, nullptr, 10);
    }
  } catch (...) {
    throw std::invalid_argument("Invalid immediate '" + imm + "'");
  }

  if (imm_val > max_val) {
    const uint16_t size_bits = log2(max_val + 1);
    throw std::invalid_argument("Immediate exceeds its " + std::to_string(size_bits) + "-bit boundaries");
  }

  return imm_val & max_val;
}

uint16_t tas::decoder::DecodeLabel(const std::string& label, const std::map<uint16_t, std::string>& program_labels) {
  const auto it = std::find_if(program_labels.cbegin(), program_labels.cend(), [&](const auto& lbl) {
    return lbl.second == label;
  });
  if (it == program_labels.cend()) {
    throw std::invalid_argument("Invalid label '" + label + "'");
  }
  return it->first;
}

uint16_t tas::decoder::CalculateLabelAddress(const std::string& label, const std::string& current_address, const std::map<uint16_t, std::string>& program_labels, bool is_jump) {
  const uint16_t mask = (is_jump) ? k12bitMask : k10bitMask;

  int16_t address = 0;

  if (label == ".") {
    address = std::stoi(current_address, nullptr, 10);
  } else {
    address = DecodeLabel(label, program_labels);
  }
  
  address = address - std::stoi(current_address) - 2;

  return address & mask;
}

uint16_t tas::decoder::DecodeInstruction(const std::vector<std::string>& instruction_elements, const std::map<uint16_t, std::string>& program_labels) {
  const instruction::Instruction* instruction_ptr = instruction::GetInstruction(instruction_elements.at(1));

  uint16_t number_operands = instruction_elements.size() - 2;

  if (instruction_ptr->number_operands != number_operands) {
    throw std::invalid_argument("Invalid instruction format. Expected " +
                                std::to_string(instruction_ptr->number_operands) + " operands. " +
                                std::to_string(number_operands) + " were informed");
  }

  uint16_t instruction_binary = instruction_ptr->binary_mask;

  switch (instruction_ptr->type) {
    case instruction::InstructionType::kTypeJump:
    case instruction::InstructionType::kTypeBranch:{
      const bool is_jmp = instruction_ptr->type == instruction::InstructionType::kTypeJump;

      int16_t immediate = 0;

      if(instruction_elements.back().at(0) == '#') {
        immediate = DecodeImmediate(instruction_elements.back().substr(1), (is_jmp) ? k12bitMask : k10bitMask);
      }
      else {
        immediate = CalculateLabelAddress(
          instruction_elements.back(), 
          instruction_elements.at(0), 
          program_labels, 
          is_jmp
        );
      }

      const uint16_t sign_extend_shift = (instruction_ptr->type == instruction::InstructionType::kTypeJump) ? (16 - 12) : (16 - 10); 
      immediate = ((int16_t) (immediate << (sign_extend_shift))) >> sign_extend_shift;
      
      const int16_t max_branch_value = ((is_jmp) ? k12bitMask : k10bitMask) >> 1;
      const int16_t min_branch_value = -max_branch_value - 1;

      if(immediate > max_branch_value || immediate < min_branch_value) {
        throw std::invalid_argument("Invalid displacement. Expected a displacement between " +
                                    std::to_string(max_branch_value) + " and " +
                                    std::to_string(min_branch_value) + " bytes");
      }

      if(instruction_ptr->type == instruction::InstructionType::kTypeBranch) {
        immediate <<= 1;
        immediate &= 0x07FC;
      }
      else {
        immediate >>= 1;
        immediate &= 0x07FF;
      }

      instruction_binary |= immediate;
      break;
    }
    
    case instruction::InstructionType::kTypeLoad:
    case instruction::InstructionType::kTypeStore:{
        uint16_t immediate = DecodeImmediate(instruction_elements.back(), k5bitMask) >> 1;

        instruction_binary |= DecodeRegister(instruction_elements.at(3)) << kRmPosition;

        if(instruction_ptr->type == instruction::InstructionType::kTypeStore) {
          immediate = ((immediate & 0b11100) << 6) | (immediate & 0b11);
          instruction_binary |= DecodeRegister(instruction_elements.at(2)) << kRnPosition;
        }
        else {
          instruction_binary |= DecodeRegister(instruction_elements.at(2)) << kRdPosition;
        }

        instruction_binary |= immediate;
      break;
    }

    case instruction::InstructionType::kTypeAlu:{
      uint32_t immediate_size = 0;

      const bool is_cmp = instruction_ptr->mnemonic == "cmp";

      const uint32_t operand_shift = (is_cmp) ? kRmPosition : kRdPosition;

      instruction_binary |= DecodeRegister(instruction_elements.at(2)) << operand_shift;

      if(instruction_ptr->number_operands == 3) {
        immediate_size = k5bitMask;
        instruction_binary |= DecodeRegister(instruction_elements.at(3)) << kRmPosition;
      }
      else {
        immediate_size = k8bitMask;
      }
      
      // Decode last operand
      if(instruction_elements.back().at(0) == '#') {
        uint16_t immediate = DecodeImmediate(instruction_elements.back().substr(1), immediate_size);

        if(is_cmp) {
          immediate = ((immediate & 0b11100000) << 3) | (immediate & 0b11111);
        }
        
        instruction_binary |= (1 << 11) | (immediate);
      }
      else {
        instruction_binary |= DecodeRegister(instruction_elements.back()) << kRnPosition;
      }
      break;
    }
    
    case instruction::InstructionType::kTypeStack:
      if(instruction_elements.at(2) == "push") {
        instruction_binary |= DecodeRegister(instruction_elements.back()) << kRnPosition;
      } else {
        instruction_binary |= DecodeRegister(instruction_elements.back()) << kRdPosition;
      }
      break;
    
    default: // instruction::InstructionType::kTypeHalt
      break;
  }

  return instruction_binary;
}
