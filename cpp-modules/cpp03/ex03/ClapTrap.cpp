#include "ClapTrap.hpp"

ClapTrap::ClapTrap() {
  this->name = "Anonymous";
  std::cout << "ClapTrap " << this->name << " Constructor call" << std::endl;
  this->hitpoints = 10;
  this->energy_points = 10;
  this->attack_damage = 0;
}

ClapTrap::ClapTrap(std::string const name) {
  std::cout << "ClapTrap " << name << " Constructor call" << std::endl;
  this->name = name;
  this->hitpoints = 10;
  this->energy_points = 10;
  this->attack_damage = 0;
}

ClapTrap::ClapTrap(ClapTrap const& obj) {
  std::cout << "ClapTrap " << this->name << " Copy constructor call"
            << std::endl;
  this->name = obj.name;
  this->hitpoints = obj.hitpoints;
  this->energy_points = obj.energy_points;
  this->attack_damage = obj.attack_damage;
}

ClapTrap::~ClapTrap() {
  std::cout << "ClapTrap " << this->name << " Distructor call" << std::endl;
}

std::string ClapTrap::getName(void) const { return (this->name); }

unsigned int ClapTrap::getHitPoints(void) const { return (this->hitpoints); }

unsigned int ClapTrap::getEnergyPoint(void) const {
  return (this->energy_points);
}

unsigned int ClapTrap::getAttackDamage(void) const {
  return (this->attack_damage);
}

void ClapTrap::attack(std::string const& target) {
  std::cout << "ClapTrap " << this->name << " attack " << target << " causing "
            << this->attack_damage << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
  std::cout << "ClapTrap " << this->name << " take Damage " << amount
            << " points!" << std::endl;
  this->hitpoints -= amount;
  if (this->hitpoints < 0) this->hitpoints = 0;
}

void ClapTrap::beRepaired(unsigned int amount) {
  std::cout << "ClapTrap " << this->name << " be repaired " << amount
            << " points" << std::endl;
  this->hitpoints += amount;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& obj) {
  std::cout << "ClapTrap " << this->name << " operator= call" << std::endl;
  this->name = obj.name;
  this->hitpoints = obj.hitpoints;
  this->energy_points = obj.energy_points;
  this->attack_damage = obj.attack_damage;
  return (*this);
}
