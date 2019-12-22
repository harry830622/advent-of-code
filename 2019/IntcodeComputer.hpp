#pragma once

#include <iostream>
#include <string>
#include <vector>

class IntcodeComputer {
 public:
  IntcodeComputer();

  bool is_terminated() const;

  void intcode(const std::string& intcode);

  void Execute(std::istream& is, std::ostream& os);
  void Reset();

 private:
  std::vector<std::string> intcode_tokens_;
  int pc_;
  int address_offset_;
  bool is_terminated_;
};
