#ifndef CURE_HPP
#define CURE_HPP

#include "AMateria.hpp"
#include "Character.hpp"

class Cure : public AMateria {
 private:
 public:
  Cure();
  Cure(const Cure& obj);
  ~Cure();
  Cure& operator=(const Cure& obj);
  void use(ICharacter& target);
  AMateria* clone() const;
};

#endif