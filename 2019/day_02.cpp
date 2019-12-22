#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <boost/tokenizer.hpp>

int compute(std::vector<std::string> tokens, int in_1, int in_2) {
  tokens[1] = std::to_string(in_1);
  tokens[2] = std::to_string(in_2);
  for (int i = 0; i < tokens.size() && std::stoi(tokens[i]) != 99; i += 4) {
    const int op = std::stoi(tokens[i]);
    const int in_1_pos = std::stoi(tokens[i + 1]);
    const int in_2_pos = std::stoi(tokens[i + 2]);
    const int out_pos = std::stoi(tokens[i + 3]);
    switch (op) {
      case 1: {
        tokens[out_pos] = std::to_string(std::stoi(tokens[in_1_pos]) + std::stoi(tokens[in_2_pos]));
        break;
      }
      case 2: {
        tokens[out_pos] = std::to_string(std::stoi(tokens[in_1_pos]) * std::stoi(tokens[in_2_pos]));
        break;
      }
      case 99: {
        break;
      }
      default: {
        std::cerr << "Invalid op" << std::endl;
        break;
      }
    }
  }
  std::stringstream ss;
  for (const auto& token : tokens) {
    ss << token << ",";
  }
  ss << std::endl;
  return std::stoi(tokens[0]);
}

int main() {
  std::string str;
  std::cin >> str;
  boost::char_separator<char> sep(",");
  boost::tokenizer<boost::char_separator<char>> tokenizer(str, sep);
  std::vector<std::string> tokens(tokenizer.begin(), tokenizer.end());
  std::cout << "Part One: " << compute(tokens, 12, 2) << std::endl;
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      if (compute(tokens, i, j) == 19690720) {
        std::cout << "Part Two: " << 100 * i + j << std::endl;
        break;
      }
    }
  }

  return 0;
}
