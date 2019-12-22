#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <array>
#include <boost/tokenizer.hpp>

std::array<int, 4> ToOpAndParamModeCodes(const std::string& code) {
  std::array<int, 4> op_and_param_mode_codes;
  op_and_param_mode_codes[0] = std::stoi(code.substr(3));
  op_and_param_mode_codes[1] = std::stoi(code.substr(2, 1));
  op_and_param_mode_codes[2] = std::stoi(code.substr(1, 1));
  op_and_param_mode_codes[3] = std::stoi(code.substr(0, 1));
  return op_and_param_mode_codes;
}

void Compute(std::vector<std::string> tokens) {
  int pc = 0;
  bool is_terminated = false;
  while (!is_terminated && pc < tokens.size()) {
    std::stringstream ss;
    ss << std::setw(5) << std::setfill('0') << std::stoi(tokens[pc]);
    const auto op_and_param_mode_codes = ToOpAndParamModeCodes(ss.str());
    const int op = op_and_param_mode_codes[0];
    const int mode_1 = op_and_param_mode_codes[1];
    const int mode_2 = op_and_param_mode_codes[2];
    const int mode_3 = op_and_param_mode_codes[3];
    switch (op) {
      case 1:
      case 2: {
        const int param_1 = std::stoi(tokens[pc + 1]);
        const int param_2 = std::stoi(tokens[pc + 2]);
        const int param_3 = std::stoi(tokens[pc + 3]);
        int in_1 = 0;
        int in_2 = 0;
        const int out_pos = param_3;
        switch (mode_1) {
          case 0: {
            in_1 = std::stoi(tokens[param_1]);
            break;
          }
          case 1: {
            in_1 = param_1;
            break;
          }
          default: {
            break;
          }
        }
        switch (mode_2) {
          case 0: {
            in_2 = std::stoi(tokens[param_2]);
            break;
          }
          case 1: {
            in_2 = param_2;
            break;
          }
          default: {
            break;
          }
        }
        switch (op) {
          case 1: {
            tokens[out_pos] = std::to_string(in_1 + in_2);
            break;
          }
          case 2: {
            tokens[out_pos] = std::to_string(in_1 * in_2);
            break;
          }
          default: {
            break;
          }
        }
        pc += 4;
        break;
      }
      case 3: {
        const int out_pos = std::stoi(tokens[pc + 1]);
        int in;
        std::cin >> in;
        tokens[out_pos] = std::to_string(in);
        pc += 2;
        break;
      }
      case 4: {
        const int in_pos = std::stoi(tokens[pc + 1]);
        std::cout << tokens[in_pos] << std::endl;
        pc += 2;
        break;
      }
      case 5:
      case 6: {
        const int param_1 = std::stoi(tokens[pc + 1]);
        const int param_2 = std::stoi(tokens[pc + 2]);
        int in = 0;
        int out = 0;
        switch (mode_1) {
          case 0: {
            in = std::stoi(tokens[param_1]);
            break;
          }
          case 1: {
            in = param_1;
            break;
          }
          default: {
            break;
          }
        }
        switch (mode_2) {
          case 0: {
            out = std::stoi(tokens[param_2]);
            break;
          }
          case 1: {
            out = param_2;
            break;
          }
          default: {
            break;
          }
        }
        switch (op) {
          case 5: {
            if (in) {
              pc = out;
            } else {
              pc += 3;
            }
            break;
          }
          case 6: {
            if (!in) {
              pc = out;
            } else {
              pc += 3;
            }
            break;
          }
          default: {
            break;
          }
        }
        break;
      }
      case 7:
      case 8: {
        const int param_1 = std::stoi(tokens[pc + 1]);
        const int param_2 = std::stoi(tokens[pc + 2]);
        const int param_3 = std::stoi(tokens[pc + 3]);
        int in_1 = 0;
        int in_2 = 0;
        const int out_pos = param_3;
        switch (mode_1) {
          case 0: {
            in_1 = std::stoi(tokens[param_1]);
            break;
          }
          case 1: {
            in_1 = param_1;
            break;
          }
          default: {
            break;
          }
        }
        switch (mode_2) {
          case 0: {
            in_2 = std::stoi(tokens[param_2]);
            break;
          }
          case 1: {
            in_2 = param_2;
            break;
          }
          default: {
            break;
          }
        }
        switch (op) {
          case 7: {
            if (in_1 < in_2) {
              tokens[out_pos] = std::to_string(1);
            } else {
              tokens[out_pos] = std::to_string(0);
            }
            break;
          }
          case 8: {
            if (in_1 == in_2) {
              tokens[out_pos] = std::to_string(1);
            } else {
              tokens[out_pos] = std::to_string(0);
            }
            break;
          }
          default: {
            break;
          }
        }
        pc += 4;
        break;
      }
      case 99: {
        is_terminated = true;
        break;
      }
      default: {
        std::cerr << "Invalid op" << std::endl;
        break;
      }
    }
  }
}

int main() {
  std::string str;
  std::cin >> str;
  boost::char_separator<char> sep(",");
  boost::tokenizer<boost::char_separator<char>> tokenizer(str, sep);
  std::vector<std::string> tokens(tokenizer.begin(), tokenizer.end());
  Compute(tokens);

  return 0;
}
