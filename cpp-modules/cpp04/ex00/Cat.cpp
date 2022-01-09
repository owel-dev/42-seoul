#include "Cat.hpp"

Cat::Cat() : Animal("Cat") { std::cout << "Cat constructor call" << std::endl; }

Cat::Cat(const Cat& obj) : Animal(obj) {
  std::cout << "Cat copy constructor call" << std::endl;
}

Cat::~Cat() { std::cout << "Cat distructor call" << std::endl; }

void Cat::makeSound(void) const { std::cout << "Cat make sound!" << std::endl; }

Cat& Cat::operator=(const Cat& obj) {
  std::cout << "Cat assign operator call" << std::endl;
  this->type = obj.getType();
  return (*this);
}