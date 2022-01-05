#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP
#include <iostream>

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {
 private:
 public:
  ScavTrap();
  ScavTrap(const std::string name);
  ScavTrap(const ScavTrap& obj);
  ~ScavTrap();
  void guardGate() const;
  ScavTrap& operator=(const ScavTrap& obj);
};

#endif
