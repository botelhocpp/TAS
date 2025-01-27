// Copyright (c) 2025 TAS
// All rights reserved

#pragma once

#include <stdexcept>

namespace tas {
namespace parser {

class ParserException : private std::exception {
 public:
  ParserException(const std::string& message, int line) noexcept;
  virtual ~ParserException() = default;
  virtual char const* what() const noexcept;
  int GetLine() const noexcept;

 private:
  std::string message;
  int line;
};

}  // namespace parser
}  // namespace tas
