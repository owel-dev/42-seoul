#ifndef ICE_HPP
#define ICE_HPP
#include "AMateria.hpp"
#include "Character.hpp"

class Ice : public AMateria {
 private:
 public:
  Ice();
  Ice(const Ice& obj);
  ~Ice();
  Ice& operator=(const Ice& obj);
  void use(ICharacter& target);
  AMateria* clone() const;
};

#endif