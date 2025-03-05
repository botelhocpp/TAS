// Copyright (c) 2025 TAS
// All rights reserved

#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace tas {
namespace instruction {

enum class InstructionType {
    kTypeJump,
    kTypeBranch,
    kTypeLoad,
    kTypeStore,
    kTypeAlu,
    kTypeControl,
    kTypeStack,
    kTypeHalt
};

struct Instruction {
    std::string mnemonic;
    uint16_t binary_mask;
    int number_operands;
    InstructionType type;
};

const Instruction* GetInstruction(const std::string& mnemonic);

void SplitInstruction(const std::string& line, std::vector<std::string>& instruction_elements);

void CleanInstruction(std::string& line);

}  // namespace instruction
}  // namespace tas
