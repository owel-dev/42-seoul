#include "Animal.hpp"

Animal::Animal() {
  std::cout << "Animal default constructor call" << std::endl;
  this->type = "Animal";
}

Animal::Animal(const std::string type) {
  std::cout << "Animal constructor call" << std::endl;
  this->type = type;
}

Animal::~Animal() { std::cout << "Animal distructor call" << std::endl; }

Animal::Animal(const Animal& obj) {
  std::cout << "Animal copy constructor call" << std::endl;
  this->type = obj.type;
}

void Animal::makeSound(void) const {
  std::cout << "Animal make sound!" << std::endl;
}

std::string Animal::getType(void) const { return (this->type); }

Animal& Animal::operator=(const Animal& obj) {
  std::cout << "Animal assign operator call" << std::endl;
  this->type = obj.type;
  return (*this);
}
