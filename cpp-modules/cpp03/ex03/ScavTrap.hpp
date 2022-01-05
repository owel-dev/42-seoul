#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP
#include <iostream>

#include "ClapTrap.hpp"

class ScavTrap : virtual public ClapTrap {
 private:
 public:
  ScavTrap();
  ScavTrap(const std::string name);
  ScavTrap(const ScavTrap& obj);
  ~ScavTrap();
  void guardGate() const;
  void attack(std::string const& target);
  ScavTrap& operator=(const ScavTrap& obj);
};

#endif
