#include "Character.hpp"

Character::Character(const std::string name) {
  this->name = name;
  for (int i = 0; i < 4; i++) this->materias[i] = NULL;
}

Character::Character(const Character& obj) { *this = obj; }

Character::~Character() {}

Character& Character::operator=(const Character& obj) {
  if (this == &obj) return (*this);
  this->name = obj.name;
  for (int i = 0; i < 4; i++) {
    if (this->materias[i] != NULL) delete this->materias[i];
    this->materias[i] = obj.materias[i]->clone();
  }
  return (*this);
}

std::string const& Character::getName() const { return (this->name); }

void Character::equip(AMateria* m) {
  for (int i = 0; i < 4; i++) {
    if (this->materias[i] == NULL) {
      this->materias[i] = m;
      return;
    }
  }
}

void Character::unequip(int idx) {
  if (0 <= idx && idx <= 3) this->materias[idx] = NULL;
}

void Character::use(int idx, ICharacter& target) {
  if (0 <= idx && idx <= 3) this->materias[idx]->use(target);
}