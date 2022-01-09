#include "Dog.hpp"

Dog::Dog() : Animal("Dog") { std::cout << "Dog constructor call" << std::endl; }

Dog::Dog(const Dog& obj) : Animal(obj) {
  std::cout << "Dog copy constructor call" << std::endl;
}

Dog::~Dog() { std::cout << "Cat distructor call" << std::endl; }

void Dog::makeSound(void) const { std::cout << "Dog make sound!" << std::endl; }

Dog& Dog::operator=(const Dog& obj) {
  std::cout << "Dog assign operator call" << std::endl;
  this->type = obj.getType();
  return (*this);
}