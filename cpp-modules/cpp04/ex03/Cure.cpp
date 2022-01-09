#include "Cure.hpp"

#include "Character.hpp"

Cure::Cure() : AMateria("cure") {}

Cure::Cure(const Cure& obj) : AMateria("cure") { *this = obj; }

Cure::~Cure() {}

Cure& Cure::operator=(const Cure& obj) {
  if (this == &obj) return (*this);
  this->AMateria::operator=(obj);
  return (*this);
}

AMateria* Cure::clone() const {
  Cure* temp = new Cure(*this);
  return (temp);
}

void Cure::use(ICharacter& target) {
  std::cout << "Cure: "
            << "\"\\* heals " << target.getName() << "\'s wounds \\*\""
            << std::endl;
}
