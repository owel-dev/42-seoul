#include <cmath>
#include <iostream>
#include <string>

#include "Scalar.hpp"

int main(int ac, char **av) {
  if (ac != 2) {
    std::cerr << "Argument error!" << std::endl;
    return (1);
  }
  Scalar sc(av[1]);
  std::cout << sc << std::endl;
}