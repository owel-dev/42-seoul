#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() {
  std::cout << "WrongAnimal default constructor call" << std::endl;
  this->type = "WrongAnimal";
}
#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(const std::string type) {
  std::cout << "WrongAnimal constructor call" << std::endl;
  this->type = type;
}

WrongAnimal::~WrongAnimal() {
  std::cout << "WrongAnimal distructor call" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& obj) {
  std::cout << "WrongAnimal copy constructor call" << std::endl;
  this->type = obj.type;
}

void WrongAnimal::makeSound(void) const {
  std::cout << "WrongAnimal make sound!" << std::endl;
}

std::string WrongAnimal::getType(void) const { return (this->type); }

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& obj) {
  std::cout << "WrongAnimal assign operator call" << std::endl;
  this->type = obj.type;
  return (*this);
}
