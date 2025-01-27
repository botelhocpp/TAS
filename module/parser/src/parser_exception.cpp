// Copyright (c) 2025 TAS
// All rights reserved

#include "module/parser/include/parser_exception.hpp"

tas::parser::ParserException::ParserException(const std::string& message, int line) noexcept
    : std::exception(), message(message), line(line) {}

char const* tas::parser::ParserException::what() const noexcept {
  return message.c_str();
}

int tas::parser::ParserException::GetLine() const noexcept {
  return line;
}
