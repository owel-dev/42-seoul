#include "MateriaSource.hpp"

MateriaSource::MateriaSource() {
  for (int i = 0; i < 4; i++) this->materias[i] = NULL;
}

MateriaSource::MateriaSource(const MateriaSource& obj) { *this = obj; }

MateriaSource::~MateriaSource() {}

MateriaSource& MateriaSource::operator=(const MateriaSource& obj) {
  if (this == &obj) return (*this);
  for (int i = 0; i < 4; i++) {
    if (this->materias[i]) delete this->materias[i];
    this->materias[i] = obj.materias[i]->clone();
  }
  return (*this);
}

void MateriaSource::learnMateria(AMateria* m) {
  for (int i = 0; i < 4; i++) {
    if (this->materias[i] == NULL) {
      this->materias[i] = m;
      return;
    }
  }
}

AMateria* MateriaSource::createMateria(std::string const& type) {
  for (int i = 0; i < 4; i++) {
    if (this->materias[i] != NULL && this->materias[i]->getType() == type) {
      return (materias[i]->clone());
    }
  }
  return (NULL);
}