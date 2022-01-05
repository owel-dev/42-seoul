#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap() {
  std::cout << "FragTrap " << this->name << " Constructor call" << std::endl;
  this->hitpoints = 100;
  this->energy_points = 100;
  this->attack_damage = 30;
}

FragTrap::FragTrap(const std::string name) : ClapTrap(name) {
  std::cout << "FragTrap " << this->name << " Constructor call" << std::endl;
}

FragTrap::~FragTrap() {
  std::cout << "FragTrap " << this->name << " Distructor call" << std::endl;
}

FragTrap::FragTrap(const FragTrap& obj) : ClapTrap(obj) {
  std::cout << "FragTrap " << this->name << " copy constructor call"
            << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& obj) {
  std::cout << "FragTrap " << this->name << " operator= call" << std::endl;
  ClapTrap::operator=(obj);
  return (*this);
}

void FragTrap::highFivesGuys(void) {
  std::cout << "FragTrap " << this->name << " high five!!!!!" << std::endl;
}
