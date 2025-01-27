// Copyright (c) 2025 TAS
// All rights reserved

#pragma once

#include "module/instruction/include/instruction.hpp"

namespace tas {
namespace instructions {

const instruction::Instruction kInstructionList[] = {
    {"jmp",  0x0800, 1, instruction::InstructionType::kTypeJump},
    {"beq",  0x1800, 1, instruction::InstructionType::kTypeBranch},
    {"bne",  0x1801, 1, instruction::InstructionType::kTypeBranch},
    {"ble",  0x1802, 1, instruction::InstructionType::kTypeBranch},
    {"bgt",  0x1803, 1, instruction::InstructionType::kTypeBranch},
    {"ldr",  0x2800, 3, instruction::InstructionType::kTypeLoad},
    {"str",  0x3800, 3, instruction::InstructionType::kTypeStore},
    {"mov",  0x4000, 2, instruction::InstructionType::kTypeAlu},
    {"add",  0x5000, 3, instruction::InstructionType::kTypeAlu},
    {"sub",  0x6000, 3, instruction::InstructionType::kTypeAlu},
    {"mul",  0x7000, 3, instruction::InstructionType::kTypeAlu},
    {"and",  0x8000, 3, instruction::InstructionType::kTypeAlu},
    {"or",   0x9000, 3, instruction::InstructionType::kTypeAlu},
    {"xor",  0xA000, 3, instruction::InstructionType::kTypeAlu},
    {"shr",  0xB000, 3, instruction::InstructionType::kTypeAlu},
    {"shl",  0xC000, 3, instruction::InstructionType::kTypeAlu},
    {"cmp",  0xD000, 2, instruction::InstructionType::kTypeAlu},
    {"not",  0xE000, 2, instruction::InstructionType::kTypeAlu},
    {"neg",  0xE001, 2, instruction::InstructionType::kTypeAlu},
    {"push", 0xF8C0, 1, instruction::InstructionType::kTypeStack},
    {"pop",  0xF8C1, 1, instruction::InstructionType::kTypeStack},
    {"halt", 0xFFFF, 0, instruction::InstructionType::kTypeHalt},
};

}
}  // namespace tas
