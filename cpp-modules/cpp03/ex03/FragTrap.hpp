#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include <iostream>

#include "ClapTrap.hpp"

class FragTrap : virtual public ClapTrap {
 private:
 public:
  FragTrap();
  FragTrap(const std::string name);
  FragTrap(const FragTrap& obj);
  ~FragTrap();
  FragTrap& operator=(const FragTrap& obj);
  void highFivesGuys(void);
};
#endif