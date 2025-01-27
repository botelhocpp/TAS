// Copyright (c) 2025 TAS
// All rights reserved

#include <algorithm>

#include "utils/strmanip/include/strmanip.hpp"

void tas::strmanip::LeftTrim(std::string &line) noexcept {
    line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

void tas::strmanip::RightTrim(std::string &line) noexcept {
    line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), line.end());
}

void tas::strmanip::MiddleTrim(std::string &line) noexcept {
  std::string::iterator new_end = std::unique(line.begin(), line.end(), [](char lhs, char rhs) {
    return (lhs == rhs) && (lhs == ' ');
  });
  line.erase(new_end, line.end());  
}

void tas::strmanip::RemoveComma(std::string& line) noexcept {
  line.erase(std::remove(line.begin(), line.end(), ','), line.end());
}

void tas::strmanip::RemoveSubstring(std::string& line, const char *substring) noexcept {
  std::size_t comment_pos = line.find(substring);
  
  if(comment_pos != std::string::npos) {
    line.erase(comment_pos);
  }
}

void tas::strmanip::RemoveChar(std::string& line, char c) noexcept {
  line.erase(std::remove(line.begin(), line.end(), c), line.end());
}

void tas::strmanip::ToUpperCase(std::string& line) noexcept {
  std::transform(line.begin(), line.end(), line.begin(), ::toupper);
}
