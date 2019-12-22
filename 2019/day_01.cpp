#include <iostream>
#include <string>
#include <algorithm>

int computeRequiredFuel(int mass) {
  return std::max(0, mass / 3 - 2);
}

int main() {
  int required_fuel_sum = 0;
  std::string str;
  while (std::cin >> str) {
    const int module_mass = std::stoi(str);
    int required_fuel = computeRequiredFuel(module_mass);
    while (required_fuel > 0) {
      required_fuel_sum += required_fuel;
      required_fuel = computeRequiredFuel(required_fuel);
    }
  }
  std::cout << required_fuel_sum << std::endl;

  return 0;
}
