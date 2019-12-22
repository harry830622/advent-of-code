#include "./IntcodeComputer.hpp"

#include <array>
#include <boost/tokenizer.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

IntcodeComputer::IntcodeComputer()
    : intcode_tokens_(1000000, "0"),
      pc_(0),
      address_offset_(0),
      is_terminated_(false) {}

bool IntcodeComputer::is_terminated() const { return is_terminated_; }

void IntcodeComputer::intcode(const std::string& intcode) {
  boost::char_separator<char> sep(",");
  boost::tokenizer<boost::char_separator<char>> tokenizer(intcode, sep);
  intcode_tokens_.assign(tokenizer.begin(), tokenizer.end());
}

void IntcodeComputer::Execute(std::istream& is, std::ostream& os) {
  bool is_halted = false;
  while (!is_terminated_ && !is_halted && pc_ < intcode_tokens_.size()) {
    std::stringstream ss;
    ss << std::setw(5) << std::setfill('0') << std::stoi(intcode_tokens_[pc_]);
    const std::string instruction(ss.str());
    const int op = std::stoi(instruction.substr(3));
    const int mode_1 = std::stoi(instruction.substr(2, 1));
    const int mode_2 = std::stoi(instruction.substr(1, 1));
    const int mode_3 = std::stoi(instruction.substr(0, 1));
    std::cout << "pc_: " << pc_ << " op: " << op << " mode_1: " << mode_1
              << " mode_2: " << mode_2 << " mode_3: " << mode_3 << std::endl;
    switch (op) {
      case 1:
      case 2: {
        const long long param_1 = std::stoi(intcode_tokens_[pc_ + 1]);
        const long long param_2 = std::stoi(intcode_tokens_[pc_ + 2]);
        const int param_3 = std::stoi(intcode_tokens_[pc_ + 3]);
        long long in_1 = 0;
        long long in_2 = 0;
        int out_pos = -1;
        switch (mode_1) {
          case 0: {
            in_1 = std::stoll(intcode_tokens_[param_1]);
            break;
          }
          case 1: {
            in_1 = param_1;
            break;
          }
          case 2: {
            in_1 = std::stoll(intcode_tokens_[address_offset_ + param_1]);
            break;
          }
          default: {
            break;
          }
        }
        switch (mode_2) {
          case 0: {
            in_2 = std::stoll(intcode_tokens_[param_2]);
            break;
          }
          case 1: {
            in_2 = param_2;
            break;
          }
          case 2: {
            in_2 = std::stoll(intcode_tokens_[address_offset_ + param_2]);
            break;
          }
          default: {
            break;
          }
        }
        switch (mode_3) {
          case 0:
          case 1: {
            out_pos = param_3;
            break;
          }
          case 2: {
            out_pos = address_offset_ + param_3;
            break;
          }
          default: {
            break;
          }
        }
        long long result = 0;
        switch (op) {
          case 1: {
            result = in_1 + in_2;
            break;
          }
          case 2: {
            result = in_1 * in_2;
            break;
          }
          default: {
            break;
          }
        }
        intcode_tokens_[out_pos] = std::to_string(result);
        pc_ += 4;
        std::cout << "in_1: " << in_1 << " in_2: " << in_2
                  << " out_pos: " << out_pos << " result: " << result
                  << std::endl;
        break;
      }
      case 3: {
        const int param_1 = std::stoi(intcode_tokens_[pc_ + 1]);
        int out_pos = -1;
        switch (mode_1) {
          case 0:
          case 1: {
            out_pos = param_1;
            break;
          }
          case 2: {
            out_pos = address_offset_ + param_1;
            break;
          }
          default: {
            break;
          }
        }
        int in;
        is >> in;
        intcode_tokens_[out_pos] = std::to_string(in);
        pc_ += 2;
        std::cout << "in: " << in << " out_pos: " << std::endl;
        break;
      }
      case 4: {
        const long long param_1 = std::stoll(intcode_tokens_[pc_ + 1]);
        long long in = 0;
        switch (mode_1) {
          case 0: {
            in = std::stoll(intcode_tokens_[param_1]);
            break;
          }
          case 1: {
            in = param_1;
            break;
          }
          case 2: {
            in = std::stoll(intcode_tokens_[address_offset_ + param_1]);
            break;
          }
          default: {
            break;
          }
        }
        os << in << std::endl;
        is_halted = true;
        pc_ += 2;
        std::cout << "in: " << in << std::endl;
        break;
      }
      case 5:
      case 6: {
        const long long param_1 = std::stoll(intcode_tokens_[pc_ + 1]);
        const long long param_2 = std::stoll(intcode_tokens_[pc_ + 2]);
        long long in = 0;
        int next_pc = -1;
        switch (mode_1) {
          case 0: {
            in = std::stoll(intcode_tokens_[param_1]);
            break;
          }
          case 1: {
            in = param_1;
            break;
          }
          case 2: {
            in = std::stoll(intcode_tokens_[address_offset_ + param_1]);
            break;
          }
          default: {
            break;
          }
        }
        switch (mode_2) {
          case 0: {
            next_pc = std::stoi(intcode_tokens_[param_2]);
            break;
          }
          case 1: {
            next_pc = param_2;
            break;
          }
          case 2: {
            next_pc = std::stoi(intcode_tokens_[address_offset_ + param_2]);
            break;
          }
          default: {
            break;
          }
        }
        switch (op) {
          case 5: {
            if (in) {
              pc_ = next_pc;
            } else {
              pc_ += 3;
            }
            break;
          }
          case 6: {
            if (!in) {
              pc_ = next_pc;
            } else {
              pc_ += 3;
            }
            break;
          }
          default: {
            break;
          }
        }
        std::cout << "in: " << in << " next_pc: " << next_pc << std::endl;
        break;
      }
      case 7:
      case 8: {
        const long long param_1 = std::stoi(intcode_tokens_[pc_ + 1]);
        const long long param_2 = std::stoi(intcode_tokens_[pc_ + 2]);
        const int param_3 = std::stoi(intcode_tokens_[pc_ + 3]);
        long long in_1 = 0;
        long long in_2 = 0;
        int out_pos = -1;
        switch (mode_1) {
          case 0: {
            in_1 = std::stoll(intcode_tokens_[param_1]);
            break;
          }
          case 1: {
            in_1 = param_1;
            break;
          }
          case 2: {
            in_1 = std::stoll(intcode_tokens_[address_offset_ + param_1]);
            break;
          }
          default: {
            break;
          }
        }
        switch (mode_2) {
          case 0: {
            in_2 = std::stoll(intcode_tokens_[param_2]);
            break;
          }
          case 1: {
            in_2 = param_2;
            break;
          }
          case 2: {
            in_2 = std::stoll(intcode_tokens_[address_offset_ + param_2]);
            break;
          }
          default: {
            break;
          }
        }
        switch (mode_3) {
          case 0:
          case 1: {
            out_pos = param_3;
            break;
          }
          case 2: {
            out_pos = address_offset_ + param_3;
            break;
          }
          default: {
            break;
          }
        }
        switch (op) {
          case 7: {
            if (in_1 < in_2) {
              intcode_tokens_[out_pos] = std::to_string(1);
            } else {
              intcode_tokens_[out_pos] = std::to_string(0);
            }
            break;
          }
          case 8: {
            if (in_1 == in_2) {
              intcode_tokens_[out_pos] = std::to_string(1);
            } else {
              intcode_tokens_[out_pos] = std::to_string(0);
            }
            break;
          }
          default: {
            break;
          }
        }
        pc_ += 4;
        std::cout << "in_1: " << in_1 << " in_2: " << in_2
                  << " out_pos: " << out_pos << " " << intcode_tokens_[out_pos]
                  << std::endl;
        break;
      }
      case 9: {
        const int param_1 = std::stoi(intcode_tokens_[pc_ + 1]);
        int offset = 0;
        switch (mode_1) {
          case 0: {
            offset = std::stoi(intcode_tokens_[param_1]);
            break;
          }
          case 1: {
            offset = param_1;
            break;
          }
          case 2: {
            offset = std::stoi(intcode_tokens_[address_offset_ + param_1]);
            break;
          }
          default: {
            break;
          }
        }
        address_offset_ += offset;
        pc_ += 2;
        std::cout << "offset: " << offset
                  << " address_offset_: " << address_offset_ << std::endl;
        break;
      }
      case 99: {
        is_halted = true;
        is_terminated_ = true;
        pc_ += 1;
        break;
      }
      default: {
        std::cerr << "Invalid op" << std::endl;
        break;
      }
    }
  }
  if (pc_ >= intcode_tokens_.size()) {
    is_terminated_ = true;
  }
}

void IntcodeComputer::Reset() {
  pc_ = 0;
  is_terminated_ = false;
}
