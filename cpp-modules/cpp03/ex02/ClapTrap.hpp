#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>

class ClapTrap {
 protected:
  std::string name;
  unsigned int hitpoints;
  unsigned int energy_points;
  unsigned int attack_damage;

 public:
  ClapTrap();
  ClapTrap(std::string const name);
  ClapTrap(ClapTrap const& obj);
  ~ClapTrap();
  void attack(std::string const& target);
  void takeDamage(unsigned int amount);
  void beRepaired(unsigned int amount);
  ClapTrap& operator=(const ClapTrap& obj);
};

#endif