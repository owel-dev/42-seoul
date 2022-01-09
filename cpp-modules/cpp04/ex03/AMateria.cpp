#include "AMateria.hpp"

AMateria::AMateria(std::string const& type) { this->type = type; }

AMateria::AMateria(const AMateria& obj) { *this = obj; }

AMateria::~AMateria() {}

AMateria& AMateria::operator=(const AMateria& obj) {
  if (this == &obj) return (*this);
  this->type = obj.type;
  return (*this);
}
std::string const& AMateria::getType() const { return (this->type); }
void AMateria::use(ICharacter&) {}