#include "ClapTrap.hpp"

ClapTrap::ClapTrap() {
  this->name = "Anonymous";
  this->hitpoints = 10;
  this->energy_points = 10;
  this->attack_damage = 0;
  std::cout << "ClapTrap " << this->name << " Constructor call" << std::endl;
}

ClapTrap::ClapTrap(std::string const name) {
  this->name = name;
  this->hitpoints = 10;
  this->energy_points = 10;
  this->attack_damage = 0;
  std::cout << "ClapTrap " << this->name << " Constructor call" << std::endl;
}

ClapTrap::ClapTrap(ClapTrap const& obj) {
  std::cout << "ClapTrap "
            << "Anonymous"
            << " Copy constructor call" << std::endl;
  this->name = obj.name;
  this->hitpoints = obj.hitpoints;
  this->energy_points = obj.energy_points;
  this->attack_damage = obj.attack_damage;
}

ClapTrap::~ClapTrap() {
  std::cout << "ClapTrap " << this->name << " Distructor call" << std::endl;
}

void ClapTrap::attack(std::string const& target) {
  std::cout << "ClapTrap " << this->name << " attack " << target << " causing "
            << this->attack_damage << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
  this->hitpoints -= amount;
  if (this->hitpoints < 0) this->hitpoints = 0;
  std::cout << "ClapTrap " << this->name << " take damage " << amount
            << " points!" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
  this->hitpoints += amount;
  std::cout << "ClapTrap " << this->name << " be repaired " << amount
            << " points!" << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& obj) {
  std::cout << "ClapTrap " << this->name << " operator= " << obj.name << " call"
            << std::endl;
  this->name = obj.name;
  this->hitpoints = obj.hitpoints;
  this->energy_points = obj.energy_points;
  this->attack_damage = obj.attack_damage;
  return (*this);
}
