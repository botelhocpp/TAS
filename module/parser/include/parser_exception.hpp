// Copyright (c) 2025 TAS
// All rights reserved

#pragma once

#include <stdexcept>

namespace tas {
namespace parser {

class ParserException : private std::exception {
 public:
  ParserException(const std::string& message, const std::string& file_and_line) noexcept;
  virtual ~ParserException() = default;
  virtual char const* what() const noexcept;
  std::string const& GetFileAndLine() const noexcept;

 private:
  std::string message;
  std::string file_and_line;
};

}  // namespace parser
}  // namespace tas
