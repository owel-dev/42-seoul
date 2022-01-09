#include "Ice.hpp"

Ice::Ice() : AMateria("ice") {}

Ice::Ice(const Ice& obj) : AMateria("ice") { *this = obj; }

Ice::~Ice() {}

Ice& Ice::operator=(const Ice& obj) {
  if (this == &obj) return (*this);
  this->AMateria::operator=(obj);
  return (*this);
}

AMateria* Ice::clone() const {
  Ice* temp = new Ice(*this);
  return (temp);
}

void Ice::use(ICharacter& target) {
  std::cout << "Ice: "
            << "\"\\* shoots an ice bolt at " << target.getName() << " \\*\""
            << std::endl;
}
