#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>

#include "./IntcodeComputer.hpp"

int main() {
  std::string str;
  std::cin >> str;

  IntcodeComputer computer;
  computer.intcode(str);

  while (!computer.is_terminated()) {
    computer.Execute(std::cin, std::cout);
  }

  return 0;
}
