#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>

#include "./IntcodeComputer.hpp"

int main() {
  std::string str;
  std::cin >> str;

  int max_out = 0;
  std::array<int, 5> phases{5, 6, 7, 8, 9};
  do {
    std::array<IntcodeComputer, 5> amplifiers;
    for (auto& amplifier : amplifiers) {
      amplifier.intcode(str);
    }

    std::stringstream iss;
    std::stringstream oss;
    const int init_in = 0;
    int last_out = init_in;
    int curr_amp_idx = 0;
    while (!amplifiers[4].is_terminated()) {
      if (curr_amp_idx < 5) {
        iss << phases[curr_amp_idx] << std::endl;
      }
      iss << last_out << std::endl;
      amplifiers[curr_amp_idx % 5].Execute(iss, oss);
      oss >> last_out;
      ++curr_amp_idx;
    }
    if (last_out > max_out) {
      max_out = last_out;
    }
  } while (std::next_permutation(phases.begin(), phases.end()));
  std::cout << max_out << std::endl;

  return 0;
}
