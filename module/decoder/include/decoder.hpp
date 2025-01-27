// Copyright (c) 2025 TAS
// All rights reserved

#pragma once

#include <string>
#include <vector>
#include <map>

#include "module/instruction/include/instruction.hpp"

namespace tas {
namespace decoder {

uint16_t DecodeRegister(const std::string& reg);

int16_t DecodeImmediate(const std::string& imm, uint16_t max_val);

uint16_t DecodeInstruction(const std::vector<std::string>& instruction_elements, const std::map<uint16_t, std::string>& program_labels);

uint16_t DecodeLabel(const std::string& label, const std::map<uint16_t, std::string>& program_labels);

uint16_t CalculateLabelAddress(const std::string& label, const std::string& current_address, const std::map<uint16_t, std::string>& program_labels, bool is_jump);

}  // namespace decoder
}  // namespace tas
