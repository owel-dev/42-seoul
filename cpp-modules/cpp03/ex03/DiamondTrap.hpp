#ifndef DIAMONDTRAP_HPP
#define DIAMONDTRAP_HPP
#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap {
 private:
  std::string name;

 public:
  DiamondTrap();
  DiamondTrap(const std::string name);
  ~DiamondTrap();
  void attack(std::string const& target);
  void whoAmI(void);
};

#endif