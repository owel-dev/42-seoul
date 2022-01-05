#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap() {
  std::cout << "ScavTrap " << this->name << " Constructor call" << std::endl;
  this->hitpoints = 100;
  this->energy_points = 50;
  this->attack_damage = 20;
}

ScavTrap::ScavTrap(const std::string name) : ClapTrap(name) {
  this->name = name;
  std::cout << "ScavTrap " << this->name << " Constructor call" << std::endl;
  this->hitpoints = 100;
  this->energy_points = 50;
  this->attack_damage = 20;
}

ScavTrap::ScavTrap(const ScavTrap& obj) : ClapTrap(obj) {
  std::cout << "ScavTrap " << this->name << " Copy constructor call"
            << std::endl;
}

ScavTrap::~ScavTrap() {
  std::cout << "ScavTrap " << this->name << " Distructor call" << std::endl;
}

void ScavTrap::guardGate() const {
  std::cout << "ScavTrap " << this->name
            << " have enterred in Gate keeper mode!" << std::endl;
};
ScavTrap& ScavTrap::operator=(const ScavTrap& obj) {
  ClapTrap::operator=(obj);
  std::cout << "ScavTrap " << this->name << " operator= call" << std::endl;
  return (*this);
}
