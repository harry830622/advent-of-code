#include <iostream>
#include <string>
#include <vector>
#include <stack>

std::vector<int> ToDigits(int n) {
  if (n <= 0) {
    return {0};
  }
  std::stack<int> reversed_digits;
  std::vector<int> digits;
  while (n > 0) {
    reversed_digits.push(n % 10);
    n /= 10;
  }
  while (!reversed_digits.empty()) {
    digits.push_back(reversed_digits.top());
    reversed_digits.pop();
  }
  return digits;
}

int main(int argc, char* argv[]) {
  const int min = std::stoi(argv[1]);
  const int max = std::stoi(argv[2]);
  int num_passwords = 0;
  for (int n = min; n <= max; ++n) {
    const auto digits = ToDigits(n);
    bool is_never_decreased = true;
    bool is_doubled = false;
    int num_repeats = 0;
    int last_digit = 0;
    for (int digit : digits) {
      if (digit < last_digit) {
        is_never_decreased = false;
        break;
      }
      if (digit == last_digit) {
        ++num_repeats;
        /* is_doubled = true; */
      } else {
        if (num_repeats == 1) {
          is_doubled = true;
        }
        num_repeats = 0;
      }
      last_digit = digit;
    }
    if (num_repeats == 1) {
      is_doubled = true;
    }
    if (is_never_decreased && is_doubled) {
      ++num_passwords;
    }
  }
  std::cout << num_passwords << std::endl;

  return 0;
}
