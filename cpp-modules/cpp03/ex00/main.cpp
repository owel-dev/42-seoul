#include "ClapTrap.hpp"

int main() {
  ClapTrap ulee("ulee");
  ulee.attack("guest");
  ulee.takeDamage(100);
  ulee.beRepaired(3);
  ClapTrap hi("hi");
  ClapTrap man("man");
}