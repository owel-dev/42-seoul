#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap()
    : ClapTrap("Anonymous_clap_name"), ScavTrap(), FragTrap() {
  this->name = "Anonymous";
  std::cout << "DiamondTrap " << this->name << " Constructor call" << std::endl;
  this->hitpoints = 100;
  this->energy_points = 50;
  this->attack_damage = 30;
}
DiamondTrap::DiamondTrap(const std::string name)
    : ClapTrap(name + "_clap_name"), ScavTrap(), FragTrap() {
  this->name = name;
  std::cout << "DiamondTrap " << this->name << " Constructor call" << std::endl;
  this->hitpoints = 100;
  this->energy_points = 50;
  this->attack_damage = 30;
}

DiamondTrap::~DiamondTrap() {
  std::cout << "DiamondTrap " << this->name << " Distructor call" << std::endl;
}

void DiamondTrap::attack(std::string const& target) {
  ScavTrap::attack(target);
}

void DiamondTrap::whoAmI(void) {
  std::cout << "name: " << this->name << std::endl;
  std::cout << "ClapTrap name: " << ClapTrap::getName() << std::endl;
}
