#include "ClapTrap.hpp"
#include "DiamondTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int main() {
  DiamondTrap d("hello");
  d.attack("hi");
  std::cout << "Diamond_hitpoints: " << d.getHitPoints() << std::endl;
  d.takeDamage(50);
  std::cout << "Diamond_hitpoints: " << d.getHitPoints() << std::endl;
  d.beRepaired(30);
  std::cout << "Diamond_hitpoints: " << d.getHitPoints() << std::endl;
  d.guardGate();
  d.highFivesGuys();
}