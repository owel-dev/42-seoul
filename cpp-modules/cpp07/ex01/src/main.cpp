#include <iostream>

#include "Iter.hpp"

int main() {
  int a[10] = {};
  char b[15] = {};
  std::string str[10] = {"one", "two",   "three", "four", "five",
                         "six", "seven", "eight", "nine", "ten"};

  iter(a, 10, printArr);
  std::cout << std::endl;
  iter(a, 10, fillArr);
  iter(a, 10, printArr);

  std::cout << std::endl;
  std::cout << std::endl;

  iter(b, 10, printArr);
  std::cout << std::endl;
  iter(b, 10, fillArr);
  iter(b, 10, printArr);

  std::cout << std::endl;
  std::cout << std::endl;

  iter(str, 10, printArr);
  std::cout << std::endl;
  iter(str, 10, fillArr);
  iter(str, 10, printArr);
  std::cout << std::endl;
}