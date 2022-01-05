#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main() {
  // ClapTrap he("he");
  ScavTrap ulee("ulee");
  ScavTrap guest("guest");
  ScavTrap man("man");
  ulee.guardGate();
  man.attack("ulee");
}