// Copyright (c) 2025 TAS
// All rights reserved

#include "module/parser/include/parser_exception.hpp"

tas::parser::ParserException::ParserException(const std::string& message, const std::string& file_and_line) noexcept
    : std::exception(), message(message), file_and_line(file_and_line) {}

char const* tas::parser::ParserException::what() const noexcept {
  return message.c_str();
}

std::string const& tas::parser::ParserException::GetFileAndLine() const noexcept {
  return file_and_line;
}
